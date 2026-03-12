#pragma once

#include "puyoPuyoAct.hpp"

class puyoBoard;
class puyoPlayPuyo; 

class puyoPuyoGravity : public puyoPuyoAct
{
    private :
        float dist;
        bool test_act(puyoBoard& board, puyoPlayPuyo& puyo) override;
    public :
        puyoPuyoGravity(int amount, float d);

        bool decline_act(puyoBoard& board, puyoPlayPuyo& puyo) override;
        void act_puyo(puyoPlayPuyo& puyo) override;
};