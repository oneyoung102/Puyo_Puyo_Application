#pragma once

#include "puyoPuyoAct.hpp"

class puyoBoard;
class puyoPlayPuyo; 

class puyoPuyoStay : public puyoPuyoAct
{
    private :
        int bonus_count;
        bool destroy;
    protected :
        bool test(puyoBoard& board,puyoPlayPuyo& puyo) override;
    public :
        puyoPuyoStay(int amount, int bonus_count);
        bool decline(puyoBoard& board,puyoPlayPuyo& puyo) override;
        void act(puyoPlayPuyo& puyo) override;
        void more_stay();
        bool broken();
};