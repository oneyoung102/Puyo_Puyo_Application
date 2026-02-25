#pragma once

#include "../puyoPrintObject.hpp"
#include "../../../puyoPage/gamePage/puyoBoard.hpp"

class puyoPrintBoard : public puyoPrintObject
{
    private :
        puyoBoard& board;
    public :
        puyoPrintBoard(puyoBoard& b, Sprite puyo, int x, int y, int life);
        void print_object(RenderWindow& w);
};