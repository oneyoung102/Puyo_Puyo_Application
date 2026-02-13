#pragma once

#include "puyoPuyoAct_temp.hpp"

class puyoBoard;
class puyoTempPuyo; 

class puyoPuyoGravity_temp : public puyoPuyoAct_temp
{
    private :
        float dist;
        bool test_act(puyoBoard& board, puyoTempPuyo& puyo);
    public :
        puyoPuyoGravity_temp(int amount);
        bool decline_act(puyoBoard& board, puyoTempPuyo& puyo);
        void act_puyo(puyoTempPuyo& puyo);
};