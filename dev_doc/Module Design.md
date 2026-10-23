---
tags:
---
使用 `namespace sn`

## 模块依赖情况

三个层级的模块
- 最底层：position，randnum
- 第二层：board
- 第三层：snake, food, renderer，pathfinder
- 最上层：主循环

第三方模块：SFML

上层依赖下层；food 依赖 board 和 snake ，snake 依赖 board；pathfinder 依赖 board，snake，food；renderer 和 主循环 依赖 SFML

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

## 随机数生成器

负责生成随机数，依赖第三方库 `random` 。随机数种子和引擎只需要初始化一次，放在命名空间内部。而分布器放在函数内部。位于 namespace sn

`int random_gen(int lower, int upper)` 
一个随机数生成器，将分布器封装，输入两个整数范围，得到一个范围内的随机整数。food 和 Snake 依赖。

```    
    std::uniform_int_distribution<int> dist_x(1, WIDTH - 1); //分布器
    std::uniform_int_distribution<int> dist_y(1, LENGTH - 1);

```

这个不能放在 .h 文件内，多个文件引用会导致冲突，放在 .cpp 文件内
```
    //随机数生成
    std::random_device rd; //种子
    std::mt19937 gen(rd()); //随机引擎
```

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

`void foodoperation(std::function<void(Pos position)> func)` 
一个回调函数，因为 food 模块依赖 snake 模块，所以不能再让 snake 依赖 food ，于是采用回调函数发送操作的方式交给 food 操作 food_position 数据

## class snake

这个模块用于管理蛇的身体以及蛇的行为

蛇的身体是坐标的集合，应该设计数据结构管理身体。吃东西抽象成在头部插入一个新的坐标。移动抽象成在头部插入一个新的坐标，并删除尾部坐标。这样的数据结够是循环队列。需要注意，蛇的身体会变长，申请一个足够大的数组

- 一个储存头部下标的变量 `head`，指向头节点的后一位（因为它指向的是下一个可以插入的位置），应该初始化为 1
- 尾部变量 `tail`，初始化为 0
- size，初始化为 1
- 一个数组，利用随机数生成器初始化 0 位置为随机坐标
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

新增 `void dataopration(std::function<void(Pos position)> func) const`
一个回调函数，这个函数不暴露内部数组，只接受外部的操作，并作用在数组元素上。依赖 `functional` 库

## class renderer

管理图形和绘图（注意，不管显示）

新的类型，灰度值，由三个整数组成的结构体，这个模块依赖它。
`struct pray{};`

### 重要的问题：给定两个不同尺度的坐标系统，如何构造一个保持棋盘几何结构的映射?

逻辑空间：$\mathcal G=\mathbb R^2$，坐标记为：$\mathbf g= \begin{bmatrix}g_x\\g_y\end{bmatrix}$ 。虽然实际蛇的位置通常取整数格点，但使用 $\mathbb R^2$ 建模，便于描述一般的坐标变换。屏幕空间：$\mathcal P=\mathbb R^2$，像素坐标记为：$\mathbf p= \begin{bmatrix}p_x\\p_y\end{bmatrix}$ 。注意，屏幕最终呈现的是离散像素网格，但图形 API 中的坐标通常可以是连续的浮点数。因此，我们先建立连续坐标映射，再讨论像素栅格化。

在像素坐标系中，定义两个基向量：$\mathbf e_x= \begin{bmatrix}1\\0\end{bmatrix}, \quad \mathbf e_y= \begin{bmatrix}0\\1\end{bmatrix}$ ，它们分别表示向右移动 1 像素、向下移动 1 像素。

但在游戏的逻辑坐标系中，我们希望每移动 1 个单位，就在像素坐标系中移动 20 像素。因此，逻辑坐标系的两个单位基向量映射为：

$T(\mathbf e_x)= \begin{bmatrix}20\\0\end{bmatrix}, \qquad T(\mathbf e_y)= \begin{bmatrix}0\\20\end{bmatrix}$

线性变换的矩阵，可以由标准基向量经过变换后的结果作为列向量构造出来。因此，变换矩阵为：

$A= \begin{bmatrix} 20&0\\ 0&20 \end{bmatrix}$ 

利用线性性：
$\begin{aligned} T(\mathbf g) &=g_xT(\mathbf e_x)+g_yT(\mathbf e_y)\\ &=A\mathbf g\\ &=\begin{bmatrix}20g_x\\20g_y\end{bmatrix} \end{aligned}$

理论上，存在两个坐标系转化的参数是 1的情况，但是在固定窗口大小和蛇速度的情况下，这也就意味着逻辑坐标会变得和窗口一样大，地图变大而速度不变，相同时间意味着相同路程，蛇会显得很慢。但是也可以操作蛇的速度，使得相同时间走的路程变大，以抵消地图变大的代价

### class Rectangle

管理方形的属性和绘制逻辑
- `unsigned int cell_size`
- `int color[3]`

```
void drawcell(sf::RenderWindow& window, Pos position);
```
在窗口指定位置画出矩形

## 主循环

主循环负责窗口管理，事件和控制控制

**一般渲染流程**
1. 初始化所有对象
2. 处理窗口事件
3. clear 清空后台帧缓冲
4. 绘制所有物体
5. display 交换缓冲区，展示画面
每一帧之后，因为会交换缓冲区，所以必须清空后台缓存，并重新绘制所有物体。双缓冲？

**主循环流程**
初始化窗口，初始化帧率，初始化蛇、食物、矩形。窗口是否开着？队列中是否存在事件？如果不存在，那么 pass；否则，处理事件：是否是 Event::close？是则关闭窗口；否则，是否键盘事件？是，则根据按下的键改变方向（改变方向需要把第三方库返回的值与第三方库的坐标比较，如果符合，就映射成一个字符，不要直接在snake内部用第三方库给的坐标，解耦。多种情况映射用 switch case）。否则 pass 。`delta_time` 是否超过指定时间？是则移动加减去指定时间；否则，pass 。头是否超过边界？是否吃到食物？清空后台帧缓冲，绘制食物，绘制蛇，display 交换缓冲区。

### 遇到的问题

我们需要获得蛇的身体，用于遍历。但是我们不能暴露数据，不能让外部修改
- 拷贝（太低效）
- const（需要外部const指针）
- 迭代器（需要获得底层地址）
- 回调函数（最终选择，见上文）

### std::optional 和 模板

```
while (const auto event = window.pollEvent())
{
	if (event->is<sf::Event::Closed>())
		window.close();
}
```

这一段不会导致死循环吗？
`windows.pollEvent()` 这个函数检查事件队列是否存在事件，如果存在，返回一个对象 `std::optional<sf::Event>` ，不存在就不会接着循环。检查这个事件的成员变量是否是 `Closed` 类型的变量，如果是就令 `windows.isOpen()` 返回 false 。用 while 是因为，每一帧用户的输入可能很多，需要逐个处理（我不了解这些对象的组成）
- `event->` 等价于 `event.value()` 
- `is<sf::Event::T>()`  会检查当前事件类型是否与 `sf::Event::T` 匹配
- `is<T>()`，返回 `bool` 类型，只判断事件类型是否匹配
- `getIf<T>()`，返回指针，匹配时获取事件数据的地址，不匹配时返回 `nullptr`

泛型编程，希望编写的代码能适用多种类型，一般一种逻辑可以用在多种类型上的时候考虑。py 和 scheme 这种动态语言天生支持泛型，但是 C++ 这类静态类型语言，需要用模板实现泛型

### 联想

我想到了高阶函数，把函数作为参数传入和返回

高阶函数抽象行为，泛型抽象类型

lambda表达式，匿名函数，临时定义的函数，一般和高阶函数配合使用

```C++
[capture](parameters) -> return_type {
    // 函数体
};

[capture]捕获列表
指定 Lambda 如何访问定义它的外部作用域中的局部变量。
```

C++实现高阶函数
- 模板
- 函数指针
- 使用 `std::function`

### 调控蛇的速度

本来速度应该让蛇本身进行的，但是我突然懒得做了，就算了，直接用主循环控制。

蛇的速度和帧率应该解耦，假设我们需要蛇的速度是 5 单位/s，根据 s=vt ，要移动一单位，需要0.2s，也即，每 0.2s 移动一次

计时器在每一次循环前记录上一个循环的时间，如果第一次循环，那么为 0 ，并累加给 delta_time ，重置计时器。如果 delta_time 超过 0.2 ，那么令蛇移动，并且 delta_time 自减 0.2

## 自动寻路器(class pathfinder)

自动寻路确实是蛇的一种行为，但“决定怎么走”和“执行移动”是两种不同的职责。把它们分开，后续实现 BFS、A* 或更安全的寻路策略时，就不必大幅修改蛇的移动逻辑

将棋盘抽象成一张 $|E|=|V|=width \times length$ 的网格图，那么问题就可以抽象成：如何找到一条从一个节点到另一个节点的路径。

`void pathfinding(board& board,snake& snake, food& food)`
利用 [[BFS]] 算法算出路径。board 是一种特殊的图，不用设计数据结构显示存储，只需要通过计算就可以得到邻接节点，这里计算过程封装成四个 lambda 表达式。临时属性用二维数组存储，每个格子都可以对应一个坐标节点。

