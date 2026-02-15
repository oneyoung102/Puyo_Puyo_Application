#pragma once

#include "puyoPrintObject.hpp"
#include "../../puyoPhase/puyoBoard.hpp"

class puyoPrintBoard : public puyoPrintObject
{
    private :
        puyoBoard& board;
        void print_puyo(RenderWindow& w,int img_x, int img_y, int px, int py);
    public :
        puyoPrintBoard(puyoBoard& b, Sprite puyo, int x, int y, int life);
        void print_object(RenderWindow& w);
};