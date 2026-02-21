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
        bool test_act(puyoBoard& board,puyoPlayPuyo& puyo) override;
    public :
        puyoPuyoStay(int amount, int b);
        bool decline_act(puyoBoard& board,puyoPlayPuyo& puyo) override;
        void act_puyo(puyoPlayPuyo& puyo) override;
        void more_stay();
        bool is_destroyed();
};