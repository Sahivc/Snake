#include "renderer.h"
#include "entities/snake.h"
#include "entities/board.h"
#include "entities/food.h"

#include <iostream>

void re::draw(const sn::snake& snake, const sn::board& board, const sn::food& food) {
    Pos point;

    for(int y = 0; y < board.get_length() + 1; ++y) {
        point.y = y;

        for(int x = 0; x < board.get_width() + 1; ++x) {
            point.x = x;

            if(point == food.get_food())
                std::cout << "*" ;
            else if(snake.iscontains(point))
                std::cout << "#" ;
            else
                std::cout << "." ;
        }

        std::cout << "\n" ;
    }

    std::cout << snake.get_grade() ;
}

