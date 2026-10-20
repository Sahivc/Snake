#include "renderer.h"
#include "entities/snake.h"
#include "entities/board.h"
#include "entities/food.h"

#include <SFML/Graphics.hpp>

void re::rectangle::drawrect(sf::RenderWindow& window, Pos position) {
    sf::RectangleShape rectangle({
        static_cast<float>(rect_size - 1), 
        static_cast<float>(rect_size - 1)
    });
    rectangle.setFillColor(sf::Color(color.value1, color.value2, color.value3));

    rectangle.setPosition({
        static_cast<float>(20 * position.x), //20是转化参数
        static_cast<float>(20 * position.y)
    });  //从逻辑坐标到像素坐标

    window.draw(rectangle);
}

