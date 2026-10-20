#pragma once

#include "common/position.h"

namespace sf {
    class RenderWindow;
    class Color;
}

namespace re{
    
    struct gray {
        int value1;
        int value2;
        int value3;
    };

    class rectangle {
        private:
            unsigned int rect_size;
            gray color;

        public:
            rectangle(unsigned int size = 20, gray coluar = {255, 255, 255}): rect_size(size), color(coluar){}
            ~rectangle() = default;
            void drawrect(sf::RenderWindow& window, Pos position);  
    };
}

