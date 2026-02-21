#pragma once

#include "puyoPuyoAct_temp.hpp"

class puyoBoard;
class puyoTempPuyo; 

class puyoPuyoVanish_temp : public puyoPuyoAct_temp
{
    private :
        float dist;
        bool test_act(puyoBoard& board, puyoTempPuyo& puyo);
    public :
        puyoPuyoVanish_temp(int amount);
        bool decline_act(puyoBoard& board, puyoTempPuyo& puyo);
        void act_puyo(puyoTempPuyo& puyo);
        bool vanish_soon();
};