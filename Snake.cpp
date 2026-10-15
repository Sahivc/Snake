#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include <conio.h>
#include <windows.h>

class Bound;
class Snake;

struct Pos {
    int x;
    int y;

    bool operator==(const Pos p)const {
        if(p.x == x && p.y == y)
            return true;
        return false; 
    } //重载运算符，只读函数，不改变内部变量以及外部变量
};

class Snake {
    private:
        int head;
        int rear;
        int size;
        Pos body[1200]; //存在栈内，这个容量怎么根据实际情况动态修改呢？还是说游戏的不可变数据需要不可变对象？
        char direction = 'r';
        int grade;

    public:
        Snake() {
            head = 1;
            rear = 0;   
            size = 1;
            body[0] = {1, 1};
            direction = 'd';
            grade = 0;
        }
        ~Snake() = default;
        void push_head(Pos p);
        void pop_tail();
        Pos get_headval();
        bool iscontains(Pos p);
        void move();
        void change_direction(char c);
        Pos next();
        bool eat();
        void gameover();
        int get_grade();
};

class Bound {
    private:
        const static int LENGTH = 20;
        const static int WIDTH = 60;
        //终端上，字符的高是宽的两倍，想要看上去舒服，需要把宽度设计为高度的偶数倍
        static Pos food;

    public:
        static bool isinside(Pos p);
        static void spawn(Snake s);
        static int get_length();
        static int get_width();
        static Pos get_food();
};

Pos Bound::food;

bool Bound::isinside(Pos p){
    if(p.x > 0 && p.y > 0 && p.x < WIDTH && p.y < LENGTH)
        return true;
    return false;    
}

void Bound::spawn(Snake s) {
    //随机数生成，我在豆包搜到的
    std::random_device rd; //种子
    std::mt19937 gen(rd()); //随机引擎
    std::uniform_int_distribution<int> dist_x(1, WIDTH - 1); //分布器
    std::uniform_int_distribution<int> dist_y(1, LENGTH - 1);

    Pos p;

    do {
        int x = dist_x(gen);
        int y = dist_y(gen);
        p = {x, y};
    } while(s.iscontains(p));

    food = p;
}

int Bound::get_length(){
    return LENGTH;
}

int Bound::get_width(){
    return WIDTH;
}

Pos Bound::get_food() {
    return food;
}


void Snake::push_head(Pos p) {
    if(size == 1200){}

    body[head] = p;

    head = (head + 1) % 1200;
    size++;
}

void Snake::pop_tail() {
    if(size == 0) {}

    rear = (rear + 1) % 1200;
    size--;
}

bool Snake::iscontains(Pos p) {
    int travl = rear;
    for(int i = 0; i < size; i++) {
        if(travl > 1199)
            travl = 0;
        if (p == body[travl])
            return true;
        travl++;
    }

    return false;
}

void Snake::move() {
    Pos p = next();

    push_head(p);
    pop_tail();
}

void Snake::change_direction(char c) {
    if(direction == 'd' && c != 'a')
        direction = c;
    else if(direction == 'a' && c != 'd')
        direction = c;
    else if(direction == 'w' && c != 's')
        direction = c;
    else if(direction == 's' && c != 'w')
        direction = c;
}

Pos Snake::next() {
    Pos p = get_headval(); //head 记录的是头部元素的后一位

    if(direction == 'd')
        p.x++;
    if(direction == 'a')
        p.x--;
    if(direction == 'w')
        p.y--;
    if(direction == 's')
        p.y++;

    return p;
}

bool Snake::eat() {
    Pos p = next();
    if(p == Bound::get_food()) {
        push_head(p);
        grade += 100;

        return true;
    }

    return false;
}

void Snake::gameover() {
    std::cout << "\033[2J\033[H";

    std::cout << "You die! Game over!\n" ;
    std::cout << "Your grade is: " << grade ;

    std::cout << "\033[?25h" ; //恢复光标

    exit(1);
}

Pos Snake::get_headval() {
    return body[(head-1+1200) % 1200];
}

int Snake::get_grade() {
    return grade;
}

void draw(Pos food, Snake s){
    Pos p;

    for(int i = 0; i < Bound::get_length() + 1; i++) {
        p.y = i;

        for(int j = 0; j < Bound::get_width() + 1; j++) {
            p.x = j;

            if(p == food)
                std::cout << "*" ;
            else if(s.iscontains(p))
                std::cout << "#" ;
            else
                std::cout << "." ;
        }

        std::cout << "\n" ;
    }

    std::cout << s.get_grade() ;
}

int main() {
    std::cout << "\033[?25l"; //隐藏光标

    Snake s;
    Bound::spawn(s);

    draw(Bound::get_food(), s);

    while(1){

        if(_kbhit()) {
            char key = _getch();

            if(key == 'q') 
                s.gameover();
            else 
                s.change_direction(key);
        }

        s.move();

        if(!Bound::isinside(s.get_headval())) {
            s.gameover();
        } else if(s.eat()) {
            Bound::spawn(s);
        }

        draw(Bound::get_food(), s);

        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        std::cout << "\033[2J\033[H";
    }

    return 0;
}

