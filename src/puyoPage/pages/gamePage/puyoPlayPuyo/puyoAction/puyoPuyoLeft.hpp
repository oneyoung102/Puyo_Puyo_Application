#pragma once

#include "puyoPuyoAct.hpp"

class puyoBoard;
class puyoPlayPuyo; 

class puyoPuyoLeft : public puyoPuyoAct
{
    private :
        float dist;
        bool test(puyoBoard& board, puyoPlayPuyo& puyo) override;
    public :
        puyoPuyoLeft(int amount, float dist);
        void act(puyoPlayPuyo& puyo) override;
};