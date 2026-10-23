#pragma once

#include "common/position.h"
#include "common/randnum.h"
#include "board.h"
#include <functional> //后面使用回调函数
#include <stack>

namespace sn{

    class snake {
        private:
            int head;
            int rear;
            int size;
            Pos body[1200]; //存在栈内，这个容量怎么根据实际情况动态修改呢？还是说游戏的不可变数据需要不可变对象？
            char direction;
            int grade;

        public:
            snake(sn::board& board) {
                head = 1;
                rear = 0;   
                size = 1;
                direction = ' ';
                grade = 0;

                int x = sn::random_number(1, board.get_width());
                int y = sn::random_number(1, board.get_length());
                body[0] = {x, y};
            }
            ~snake() = default;
            void push_head(Pos point);
            void pop_tail();
            bool iscontains(Pos point) const;
            void change_direction(char new_direction);
            Pos next() const;
            void move(std::stack<Pos>& path);
            bool eat(Pos position);
            Pos get_headval() const;
            int get_grade() const;
            const Pos* get_body() const;
            int get_head() const;
            int get_tail() const;
            void dataopration(std::function<void(Pos point)> func) const;
            char get_derection()const;
    };

}

