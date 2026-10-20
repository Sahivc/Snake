#pragma once

#include "common/position.h"

namespace sn{

    class board {
        private:
            int width;
            int length;  //终端上，字符的高是宽的两倍，想要看上去舒服，需要把宽度设计为高度的偶数倍

        public:
            board(int _width = 40,int _length = 30): width(_width), length(_length){}
            ~board() = default;
            bool isinside(Pos point) const;
            int get_length() const;
            int get_width() const;
        };

}

