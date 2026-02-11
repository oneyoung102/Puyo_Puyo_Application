#pragma once

#include <tuple>
#include <utility>
#include <cmath>
#include <functional>


using namespace std;

class puyoPuyoGravity;
class puyoBoard;

class puyoTempPuyo//플레이어가 움직이는 뿌요
{
    private :
        float x, y;
        int color;
        puyoPuyoGravity* gravity;

    public :
        puyoTempPuyo(float xx, float yy, int c);

        bool act_gravity(puyoBoard& board);

        bool deploy_puyo(puyoBoard& board);

        bool puyo_touched(puyoBoard& board, int ix, int iy);

        tuple<float,float> get_puyo_pos();
        void move_puyo(float to_x, float to_y);
        int get_puyo_color();
};