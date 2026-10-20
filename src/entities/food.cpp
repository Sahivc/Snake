#include "food.h"
#include "snake.h"
#include "board.h"

#include <random>

std::random_device rd; //种子
std::mt19937 gen(rd()); //随机引擎

void sn::food::spawn(const sn::snake& snake, const sn::board& board) {
    std::uniform_int_distribution<int> dist_x(1, board.get_width() - 1); //分布器
    std::uniform_int_distribution<int> dist_y(1, board.get_length() - 1);

    Pos point;

    do {
        int x = dist_x(gen);
        int y = dist_y(gen);
        point = {x, y};
    } while(snake.iscontains(point));

    food_position = point;
}

void sn::food::foodoperation(std::function<void(Pos position)> func) {
    func(food_position);
}

