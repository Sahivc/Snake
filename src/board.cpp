#include "board.h"
#include "snake.h"

#include <random>

std::random_device rd; //种子
std::mt19937 gen(rd()); //随机引擎

// 以下是 class board
bool bd::board::isinside(Pos point) const{
    if(point.x > 0 && point.y > 0 && 
        point.x < width && point.y < length)
        return true;
    return false;    
}

int bd::board::get_length() const{
    return length;
}

int bd::board::get_width() const{
    return width;
}

//以下是 class food
void bd::food::spawn(const sn::snake& snake, const bd::board& board) {
    std::uniform_int_distribution<int> dist_x(1, board.get_width() - 1); //分布器
    std::uniform_int_distribution<int> dist_y(1, board.get_length() - 1);

    Pos point;

    do {
        int x = dist_x(gen);
        int y = dist_y(gen);
        point = {x, y};
    } while(snake.iscontains(point));

    food_p = point;
}

Pos bd::food::get_food() const{
    return food_p;
}

