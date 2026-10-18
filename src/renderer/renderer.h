#pragma once

namespace sn {
    class board;
    class snake;
    class food;
}

namespace re{
    void draw(
        const sn::snake& snake, 
        const sn::board& board,
        const sn::food& food
    );
}

