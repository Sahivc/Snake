#include "food.h"
#include "snake.h"
#include "board.h"
#include "common/randnum.h"

void sn::food::spawn(const sn::snake& snake, const sn::board& board) {
    Pos point;

    do {
        int x = sn::random_number(1, board.get_width() - 1);
        int y = sn::random_number(1, board.get_length() - 1);
        point = {x, y};
    } while(snake.iscontains(point));

    food_position = point;
}

void sn::food::foodoperation(std::function<void(Pos position)> func) {
    func(food_position);
}

Pos sn::food::get_food() {
    return food_position;
}

