#pragma once

#include "puyoPuyoAct_temp.hpp"

class puyoBoard;
class puyoPuyo; 

class puyoPuyoFly_temp : public puyoPuyoAct_temp
{
    private :
        int from_x, from_y, to_x, to_y;
        bool test(puyoBoard& board, puyoPuyo& puyo);
    public :
        puyoPuyoFly_temp(float fx, float fy, float tx, float ty,int amount);
        bool decline(puyoBoard& board, puyoPuyo& puyo);
        void act(puyoPuyo& puyo);
};