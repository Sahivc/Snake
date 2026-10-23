#include "pathfinder.h"
#include "entities/board.h"
#include "entities/snake.h"
#include "entities/food.h"

std::stack<Pos> sn::pathfinder::pathfinding(sn::board& board, sn::snake& snake, sn::food& food){
    struct property {
        bool mark = 0;
        Pos parent;
    };

    //储存图的临时属性
    property graph[board.get_length()][board.get_width()];
    
    //隐式图的存储方式：计算
    auto point_left = [](Pos point){
        return Pos{point.x - 1, point.y};
    };
    
    auto point_right = [](Pos point){
        return Pos{point.x + 1, point.y};
    };
    
    auto point_up = [](Pos point){
        return Pos{point.x, point.y - 1};
    };

    auto point_down = [](Pos point){
        return Pos{point.x, point.y + 1};
    };

    //初始化
    std::queue<Pos> todo;
    std::stack<Pos> path;

    Pos begin = snake.get_headval();
    graph[begin.y][begin.x].mark = 1;
    graph[begin.y][begin.x].parent = {-1, -1};
    todo.push(begin);

    //循环中需要拿到这几个节点，先初始化，方便用
    Pos process;
    Pos left;
    Pos right;
    Pos up;
    Pos down;
    while(!todo.empty()) { //队列不为空时进行搜索
        process = todo.front();
        todo.pop();

        if(process == food.get_food()) {
            break;
        }  //显示判断是否找到食物，终止条件

        left = point_left(process);
        right = point_right(process);
        up = point_up(process);
        down = point_down(process);

        if(left.x >= 0 &&
        left.x < board.get_width() &&
        left.y >= 0 &&
        left.y < board.get_length() &&  // 此时才能访问 graph[left.y][left.x]
        snake.get_derection() != 'D' && 
        graph[left.y][left.x].mark == 0) {

            todo.push(left);
            graph[left.y][left.x].mark = 1;
            graph[left.y][left.x].parent = process;
        }

        if(right.x >= 0 &&
        right.x < board.get_width() &&
        right.y >= 0 &&
        right.y < board.get_length() &&  // 此时才能访问 graph[right.y][right.x]
        snake.get_derection() != 'A' && 
        graph[right.y][right.x].mark == 0) {

            todo.push(right);
            graph[right.y][right.x].mark = 1;
            graph[right.y][right.x].parent = process;
        }

        if(up.x >= 0 &&
        up.x < board.get_width() &&
        up.y >= 0 &&
        up.y < board.get_length() &&  // 此时才能访问 graph[up.y][up.x]
        snake.get_derection() != 'S' && 
        graph[up.y][up.x].mark == 0) {

            todo.push(up);
            graph[up.y][up.x].mark = 1;
            graph[up.y][up.x].parent = process;
        }

        if(down.x >= 0 &&
        down.x < board.get_width() &&
        down.y >= 0 &&
        down.y < board.get_length() &&// 此时才能访问 graph[down.y][down.x]
        snake.get_derection() != 'W' && 
        graph[down.y][down.x].mark == 0) {

            todo.push(down);
            graph[down.y][down.x].mark = 1;
            graph[down.y][down.x].parent = process;
        }

    }

    for(Pos travl = process; travl != Pos{-1, -1};) {
        path.push(travl);
        travl = graph[travl.y][travl.x].parent;
    }

    return path;
}

