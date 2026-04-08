#pragma once

#include "puyoPuyoAct_temp.hpp"

class puyoBoard;
class puyoPuyo; 

class puyoPuyoGravity_temp : public puyoPuyoAct_temp
{
    private :
        float dist;
        bool test(puyoBoard& board, puyoPuyo& puyo);
    public :
        puyoPuyoGravity_temp(int amount);
        bool decline(puyoBoard& board, puyoPuyo& puyo);
        void act(puyoPuyo& puyo);
};