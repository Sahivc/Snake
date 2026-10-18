#pragma once

struct Pos {
    int x;
    int y;

    bool operator==(const Pos point)const {
        if(point.x == x && point.y == y)
            return true;
        return false; 
    } //重载运算符，只读函数，不改变内部变量以及外部变量
};

