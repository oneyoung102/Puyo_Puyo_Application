#pragma once

#include "puyoPuyoAct.hpp"

class puyoBoard;
class puyoPlayPuyo; 

class puyoPuyoGravity : public puyoPuyoAct
{
    private :
        float dist;
        bool test(puyoBoard& board, puyoPlayPuyo& puyo) override;
    public :
        puyoPuyoGravity(int amount, float dist);

        bool decline(puyoBoard& board, puyoPlayPuyo& puyo) override;
        void act(puyoPlayPuyo& puyo) override;
};