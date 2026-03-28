#pragma once

#include <utility>
#include "puyoPage/pages/gamePage/puyoBoard/puyoType.hpp"

class puyoBoard;

class puyoTempPuyo
{
    protected :
        float x, y;
        puyoType color;
    public :
        puyoTempPuyo(float xx, float yy, puyoType c);

        bool puyo_touched(puyoBoard& board, int ix, int iy);
        std::pair<float,float> get_puyo_pos();
        void move_puyo(float to_x, float to_y);
        puyoType get_puyo_color();
};