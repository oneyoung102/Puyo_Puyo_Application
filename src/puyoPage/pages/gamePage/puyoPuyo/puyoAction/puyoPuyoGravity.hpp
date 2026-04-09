#pragma once

#include "puyoPuyoAct.hpp"

class puyoBoard;
class puyoPuyo; 

class puyoPuyoGravity : public puyoPuyoAct
{
    private :
        int stay;
        const int stay_value;
        bool test(puyoBoard& board, puyoPuyo& puyo) override;
        void arrive(puyoPuyo& puyo) override;
    public :
        puyoPuyoGravity(int amount, int stay_value);
        bool decline(puyoBoard& board,puyoPuyo& puyo) override;
        void act(puyoPuyo& puyo) override;
};