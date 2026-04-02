#pragma once

#include "puyoPuyoAct.hpp"

class puyoBoard;
class puyoPlayPuyo; 

class puyoPuyoLeft : public puyoPuyoAct
{
    private :
        float dist;
        bool test_act(puyoBoard& board, puyoPlayPuyo& puyo) override;
    public :
        puyoPuyoLeft(int amount, float dist);
        void act_puyo(puyoPlayPuyo& puyo) override;
};