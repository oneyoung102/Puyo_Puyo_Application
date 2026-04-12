#pragma once

#include "puyoPuyoAct.hpp"

class puyoBoard;
class puyoPuyo; 

class puyoPuyoGravity : public puyoPuyoAct
{
    private :
        bool test(puyoBoard& board, puyoPuyo& puyo) override;
        void arrive(puyoPuyo& puyo) override;
    public :
        puyoPuyoGravity(int amount);
        bool decline(puyoBoard& board,puyoPuyo& puyo) override;
        void act(puyoPuyo& puyo) override;
};