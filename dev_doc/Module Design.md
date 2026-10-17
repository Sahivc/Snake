---
tags:
---
**画模块依赖图**，模块依赖图要精确到类，文件还是接口？

## 坐标

终端可以看作坐标系，只不过把 y 轴负轴作为正轴（不加坐标转换。）

因为所有模块都依赖它，所以抽象出来了

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

## namespace bd

棋盘这个模块的职责：
- 管理 board
- 管理 food

这个模块依赖后面的 Snake 模块，应该放在其后面

### class board

```cpp
int width;
int length;
```

`width` 是 x 的边界；`length` 是 y 的边界

食物坐标 `Pos food_position` 

`bool isinside(Pos point) const` 
判断给定坐标有没有超出边界。超出边界会返回 `true`，否则返回 `false` 。主要用于判定蛇的头有没有超出边界

`int get_length() const`，`int get_width() const`
获得数据。后面渲染需要

### class food

```
Pos food_p; 
```

`Pos spawn(const snake& snake, const board& board)`
生成新的食物坐标并改变成员变量 food_p。我们需要先判断生成的坐标是否在蛇的身上，所以需要参数  `snake& snake`；因为需要不能超出边界，所以需要参数 `board& board`

```
    //随机数生成，我在豆包搜到的
    std::random_device rd; //种子
    std::mt19937 gen(rd()); //随机引擎
```

```    
    std::uniform_int_distribution<int> dist_x(1, WIDTH - 1); //分布器
    std::uniform_int_distribution<int> dist_y(1, LENGTH - 1);
    
    Pos p;
    
	do {
		int x = dist_x(gen);
		int y = dist_y(gen);
		p = {x, y};
    } while(s.iscontains(p));
	
    food_ = point;
```

上面的代码依赖第三方库 `random` 。随机数种子和引擎只需要初始化一次，放在命名空间内部。而分布器放在 `spawn` 内部。

`Pos get_food() const`
获得食物坐标，后面有用

## namespace sn

这个模块用于管理蛇的身体以及蛇的行为

### class snake

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

`bool eat(food& food)`
输出一个布尔值，在主循环中需要判断是否吃到**食物**，以此来决定接下来的行为。监测下一个坐标是否是食物坐标，如果是，那么压入，调用 `push_head()`，并且 grade+100，返回 true。返回 false

`Pos get_headval() const`
获取头部值。输入无，输出坐标。后面判断是否越界有用

`int get_grade() const`
取得分数，输入无，返回一个分数。渲染有用

## namespace rd

### class renderer

`void draw(const snake& snake, const board& board)` 
棋盘用 `.` or ` ` ，蛇用 `#` ，食物用 `*`。遍历棋盘中的每个点，判断这个点在哪个对象的范围内，接着打印。

