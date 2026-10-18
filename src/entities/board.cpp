#include "board.h"

// 以下是 class board
bool sn::board::isinside(Pos point) const{
    if(point.x > 0 && point.y > 0 && 
        point.x < width && point.y < length)
        return true;
    return false;    
}

int sn::board::get_length() const{
    return length;
}

int sn::board::get_width() const{
    return width;
}

