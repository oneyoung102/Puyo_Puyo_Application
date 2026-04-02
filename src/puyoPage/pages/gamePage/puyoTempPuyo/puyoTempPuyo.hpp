#pragma once

#include <utility>
#include "puyoPage/pages/gamePage/puyoBoard/puyoType.hpp"

class puyoBoard;

class puyoTempPuyo
{
    protected :
        float x, y;
        puyoType type;
    public :
        puyoTempPuyo(float x, float y, puyoType type);

        bool puyo_touched(puyoBoard& board, int ix, int iy);
        std::pair<float,float> get_puyo_pos();
        void move_puyo(float to_x, float to_y);
        puyoType get_puyo_type();
};