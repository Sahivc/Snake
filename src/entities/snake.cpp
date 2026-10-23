
#include "snake.h"

void sn::snake::push_head(Pos point) {
    if(size == 1200){}

    body[head] = point;

    head = (head + 1) % 1200;
    size++;
}

void sn::snake::pop_tail() {
    if(size == 0) {}

    rear = (rear + 1) % 1200;
    size--;
}

bool sn::snake::iscontains(Pos point) const{
    for(int travl = rear; travl < head; ) {
        if (point == body[travl])
            return true;
        travl = (travl + 1) % 1200;
    }

    return false;
}

void sn::snake::change_direction(char new_direction) {
    if(direction == 'D' && new_direction != 'A')
        direction = new_direction;
    else if(direction == 'A' && new_direction != 'D')
        direction = new_direction;
    else if(direction == 'W' && new_direction != 'S')
        direction = new_direction;
    else if(direction == 'S' && new_direction != 'W')
        direction = new_direction;
    else if(direction == ' ')
        direction = new_direction;
}

Pos sn::snake::next() const{
    Pos point = get_headval(); //head 记录的是头部元素的后一位

    if(direction == 'D')
        point.x++;
    if(direction == 'A')
        point.x--;
    if(direction == 'W')
        point.y--;
    if(direction == 'S')
        point.y++;

    return point;
}

void sn::snake::move(std::stack<Pos>& path) {
    if(path.empty()){
        push_head(next());
    } 
    else {
        push_head(path.top());
        path.pop();
    }

    pop_tail();
}

bool sn::snake::eat(Pos position) {
    Pos point = next();
    if(point == position) {
        push_head(point);
        grade += 1000;

        return true;
    }

    return false;
}

Pos sn::snake::get_headval() const{
    return body[(head-1+1200) % 1200];
}

int sn::snake::get_grade() const{
    return grade;
}

const Pos* sn::snake::get_body() const{
    const Pos* snake_body = body; 
    return snake_body;
}

int sn::snake::get_head() const{
    return head;
}

int sn::snake::get_tail() const{
    return rear;
}

void sn::snake::dataopration(std::function<void(Pos point)> func)const {
    for(int travl = rear; travl < head; travl = (travl + 1) % 1200) {
        func(body[travl]);
    }
} //这里是回调函数(基于高阶函数实现），用 std::functional

char sn::snake::get_derection()const {
    return direction;
}
