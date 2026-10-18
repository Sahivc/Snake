
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
    if(direction == 'd' && new_direction != 'a')
        direction = new_direction;
    else if(direction == 'a' && new_direction != 'd')
        direction = new_direction;
    else if(direction == 'w' && new_direction != 's')
        direction = new_direction;
    else if(direction == 's' && new_direction != 'w')
        direction = new_direction;
}

Pos sn::snake::next() const{
    Pos point = get_headval(); //head 记录的是头部元素的后一位

    if(direction == 'd')
        point.x++;
    if(direction == 'a')
        point.x--;
    if(direction == 'w')
        point.y--;
    if(direction == 's')
        point.y++;

    return point;
}

void sn::snake::move() {
    push_head(next());
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

