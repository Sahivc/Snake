#pragma once

namespace sn {
    class snake;
}

namespace bd {
    class board;
    class food;
}

namespace re{
    void draw(
        const sn::snake& snake, 
        const bd::board& board,
        const bd::food& food
    );
}

