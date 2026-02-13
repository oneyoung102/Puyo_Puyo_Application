#pragma once

#include <tuple>
#include <utility>
#include <cmath>

using namespace std;

class puyoBoard;

class puyoTempPuyo
{
    private :
        float x, y;
        int color;
    public :
        puyoTempPuyo(float xx, float yy, int c);

        bool deploy_puyo(puyoBoard& board);
        bool puyo_touched(puyoBoard& board, int ix, int iy);
        tuple<float,float> get_puyo_pos();
        void move_puyo(float to_x, float to_y);
        int get_puyo_color();
};