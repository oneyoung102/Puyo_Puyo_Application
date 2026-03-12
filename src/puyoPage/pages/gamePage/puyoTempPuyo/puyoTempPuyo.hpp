#pragma once

#include <utility>

class puyoBoard;

class puyoTempPuyo
{
    protected :
        float x, y;
        int color;
    public :
        puyoTempPuyo(float xx, float yy, int c);

        bool puyo_touched(puyoBoard& board, int ix, int iy);
        std::pair<float,float> get_puyo_pos();
        void move_puyo(float to_x, float to_y);
        int get_puyo_color();
};