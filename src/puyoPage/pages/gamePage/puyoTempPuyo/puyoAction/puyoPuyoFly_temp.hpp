#pragma once

#include "puyoPuyoAct_temp.hpp"

class puyoBoard;
class puyoTempPuyo; 

class puyoPuyoFly_temp : public puyoPuyoAct_temp
{
    private :
        int from_x, from_y, to_x, to_y;
        bool test_act(puyoBoard& board, puyoTempPuyo& puyo);
    public :
        puyoPuyoFly_temp(float fx, float fy, float tx, float ty,int amount);
        bool decline_act(puyoBoard& board, puyoTempPuyo& puyo);
        void act_puyo(puyoTempPuyo& puyo);
};