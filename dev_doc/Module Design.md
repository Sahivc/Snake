---
tags:
---
使用 `namespace snake`

## 基础类型：坐标

终端可以看作坐标系，只不过把 y 轴负轴作为正轴（不加坐标转换。）

管理坐标

```cpp
struct Pos {
	int x;
	int y;
	
	bool operator==(const Pos p)const {
	if(p.x == x && p.y == y)
		return true;
	return false; 
}; //重载运算符，只读函数，不改变内部变量以及外部变量
```

一个结构体，坐标由两个 `int` 组成。由于终端打印离散字符，所以坐标也应该是整数，而非浮点数。之后换了图形库可以更改成 `double` 

`bool operator==(const Pos p)const`
我们需要重载运算符，使得两个坐标相等被定义。

## class board

管理边界，判定坐标是否超出边界

```cpp
int width;
int length;
```

`width` 是 x 的边界；`length` 是 y 的边界

`bool isinside(Pos point) const` 
判断给定坐标有没有超出边界。超出边界会返回 `true`，否则返回 `false` 。主要用于判定蛇的头有没有超出边界

`int get_length() const`，`int get_width() const`
获得数据。后面渲染需要

## class food

管理食物的位置和生成

```
Pos food_position; 
```

`void spawn(snake& snake, board& board)`
生成新的食物坐标并改变成员变量 food_point。我们需要先判断生成的坐标是否在蛇的身上，以及不能越界，依赖 snake 和 board 两个模块

```
    //随机数生成，我在豆包搜到的
    std::random_device rd; //种子
    std::mt19937 gen(rd()); //随机引擎
```

```    
    std::uniform_int_distribution<int> dist_x(1, WIDTH - 1); //分布器
    std::uniform_int_distribution<int> dist_y(1, LENGTH - 1);

```

上面的代码依赖第三方库 `random` 。随机数种子和引擎只需要初始化一次，放在命名空间内部。而分布器放在 `spawn` 内部。

`Pos get_food() const`
获得食物坐标，后面有用

## class snake

这个模块用于管理蛇的身体以及蛇的行为

蛇的身体是坐标的集合，应该设计数据结构管理身体。吃东西抽象成在头部插入一个新的坐标。移动抽象成在头部插入一个新的坐标，并删除尾部坐标。这样的数据结够是循环队列。需要注意，蛇的身体会变长，申请一个足够大的数组

- 一个储存头部下标的变量 `head`，指向头节点的后一位（因为它指向的是下一个可以插入的位置），应该初始化为 1
- 尾部变量 `tail`，初始化为 0
- size，初始化为 1
- 一个数组，初始化 0 位置处的坐标为 (1, 1)
- 因为贪吃蛇的移动特性，需要加上一个 direction，初始向右
- grade

`void push_head(Pos point)`
在蛇头加入位置 p

`void pop_tail()`
删除蛇尾位置

`bool iscontains(Pos point) const`
判断身体是否包含坐标。渲染层有用

`void change_direction(char new_direction)`
将 `direction` 变成传入的方向。

`Pos next() const`
根据 `direction`，计算出下一个位置的坐标。如果向左移动，那么下一个坐标就是头部 $x-1$ ，向右则是 $x+1$，向上 $y-1$，向下$y+1$。

`void move()`
调用 `push_head(next())` 将计算出来的下一个坐标压入，最后调用 `pop_tail()`

`bool eat(Pos point)`
输出一个布尔值，在主循环中需要判断是否吃到**食物**，以此来决定接下来的行为。监测下一个坐标是否是食物坐标，如果是，那么压入，调用 `push_head()`，并且 grade+100，返回 true。返回 false

`Pos get_headval() const`
获取头部值。输入无，输出坐标。后面判断是否越界有用

`int get_grade() const`
取得分数，输入无，返回一个分数。渲染有用

## class renderer

负责渲染

`void draw(const snake& snake, const board& board)` 
棋盘用 `.` or ` ` ，蛇用 `#` ，食物用 `*`。遍历棋盘中的每个点，判断这个点在哪个对象的范围内，接着打印。依赖前三个模块

## namespace gm

放在 game_mediator 内部，由于 board, snake, food, renderer 之间处于同一层级，并且会互相产生循环依赖，所以需要一个 game 模块来协调这些模块之间的依赖，实现解耦

`bool eat_food(snake& snake, food& food)`
将食物的坐标传递给 `eat()`。由于 food 模块已经依赖 snake 模块，为了防止循环依赖， snake 的 `eat()` 依赖 food_position ，所以传入的参数改成 `Pos point`

