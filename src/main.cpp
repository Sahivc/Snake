#include "entities/snake.h"
#include "entities/board.h"
#include "entities/food.h"
#include "renderer/renderer.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

int main() {
    //初始化窗口
    sn::board board;
    sf::RenderWindow window(
        sf::VideoMode({800, 600}),
        "Snake"
    );

    window.setFramerateLimit(60);

    //初始化对象
    sn::snake snake;
    sn::food food(snake, board);

    re::rectangle rectangle;

    sf::Clock timer;
    sf::Time delta_time;

    while(window.isOpen()) {
        delta_time += timer.restart();
        //监听输入
        while(const auto event = window.pollEvent()) {
            if(event->is<sf::Event::Closed>()) { //事件是否是关闭？
                window.close();
            } 
            else if(const auto* key = event->getIf<sf::Event::KeyPressed>()) { //事件是否是用户按下了键盘？，记录键
                switch(key->code) {
                    case sf::Keyboard::Key::W :
                        snake.change_direction('W');
                        break;
                    case sf::Keyboard::Key::S :
                        snake.change_direction('S');
                        break;
                    case sf::Keyboard::Key::A :
                        snake.change_direction('A');
                        break;
                    case sf::Keyboard::Key::D :
                        snake.change_direction('D');
                        break;
                    default:
                        break;
                }
            }
        }

        if(delta_time > sf::seconds(0.1f)) {
            snake.move();
            delta_time -= sf::seconds(0.1f);
        }

        if(!board.isinside(snake.get_headval())) {
            window.close();
        } 
        else {
            food.foodoperation(
                [&snake, &food, &board](Pos position) {
                    if (snake.eat(position))
                        food.spawn(snake, board);
                }
            );
        }

        //绘制图形
        window.clear(sf::Color(25, 25, 30)); //清空后台帧缓冲

        food.foodoperation(
            [&window, &rectangle](Pos position) {
                rectangle.drawrect(window, position);
            }
        ); //使用回调函数，绘制 food
        
        snake.dataopration(
            [&window, &rectangle](Pos point) {
                rectangle.drawrect(window, point);
            }
        ); //使用回调函数，画出蛇的身体
        
        window.display();
    }

    return 0;
}

