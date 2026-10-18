#include "entities/snake.h"
#include "entities/board.h"
#include "entities/food.h"
#include "renderer/renderer.h"
#include "game/game_mediator.h"

#include <iostream>
#include <conio.h>
#include <chrono>
#include <thread>

int main() {
    std::cout << "\033[?25l"; //隐藏光标

    sn::board board;
    sn::snake snake;
    sn::food food(snake, board);

    re::draw(snake, board, food);

    while(1){

        if(_kbhit()) {
            char key = _getch();

            if(key == 'q') {
                std::cout << "\033[2J\033[H" ;
                std::cout << "Game Over!\n" << snake.get_grade() ;
                std::cout << "\033[?25h" ;
                exit(1);
            }else {
                snake.change_direction(key);
            }  
        }

        snake.move();

        if(!board.isinside(snake.get_headval())) {
            std::cout << "\033[2J\033[H" ;
            std::cout << "Game Over!\n" << snake.get_grade() ;
            std::cout << "\033[?25h" ;
            exit(1);            
        } else if(gm::eat_food(snake, food)) {
            food.spawn(snake, board);
        }

        re::draw(snake, board, food);

        std::this_thread::sleep_for(
            std::chrono::milliseconds(100)
        );

        std::cout << "\033[2J\033[H";
    }

    return 0;
}

