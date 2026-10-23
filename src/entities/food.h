#pragma once

#include "common/position.h"

#include <functional>

namespace sn{
    class snake;
    class board;
}

namespace sn{

    class food {
        private:
            Pos food_position;   
        public:
            food(sn::snake& snake, sn::board& board) {
                spawn(snake, board);
            }
            ~food() = default;
            void spawn(const sn::snake& snake, const sn::board& board);
            void foodoperation(std::function<void(Pos position)> func);
            Pos get_food();
    };

}

