#pragma once

#include "position.h"

namespace sn{
    class snake;
}

namespace bd{

    class board {
        private:
            int width;
            int length;  //终端上，字符的高是宽的两倍，想要看上去舒服，需要把宽度设计为高度的偶数倍

        public:
            board(int _width = 60,int _length = 20): width(_width), length(_length){}
            ~board() = default;
            bool isinside(Pos point) const;
            int get_length() const;
            int get_width() const;
        };
        
        class food {
            private:
                Pos food_p;   
            public:
                food(sn::snake& snake, bd::board& board) {
                    spawn(snake, board);
                }
                ~food() = default;
                void spawn(const sn::snake& snake, const bd::board& board);
                Pos get_food() const;
        };

}

