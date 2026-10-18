#pragma once

#include "common/position.h"

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
            Pos get_food() const;
    };

}