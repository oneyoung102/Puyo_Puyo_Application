#pragma once

#include "puyoPuyoAct.hpp"

class puyoBoard;
class puyoPlayPuyo; 

class puyoPuyoUp : public puyoPuyoAct
{
    private :
        float dist;
        bool test(puyoBoard& board, puyoPlayPuyo& puyo) override;
    public :
        puyoPuyoUp(int amount, float dist);

        void act(puyoPlayPuyo& puyo) override;
};