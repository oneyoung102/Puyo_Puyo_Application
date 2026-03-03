#pragma once

#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"

class puyoPrintBoard : public puyoPrintObject
{
    private :
        puyoBoard& board;
    public :
        puyoPrintBoard(puyoBoard& b, Sprite puyo, int x, int y, int life);
        void print_object(RenderWindow& w);
};