#pragma

#include "common/position.h"
#include <stack>
#include <queue>

namespace sn {
    class board;
    class snake;
    class food;
}

namespace sn {

    class pathfinder {
        public:
            pathfinder(){}
            ~pathfinder() = default;
            std::stack<Pos> pathfinding(sn::board& board, sn::snake& snake, sn::food& food);
    };

}

