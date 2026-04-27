#pragma once

#include "puyoPuyoAct.hpp"
#include "puyoPos.hpp"

class puyoBoard;
class puyoPlayPuyo; 

class puyoPuyoFourWayMove : public puyoPuyoAct
{
    private :
        const POSf dpos;
        bool test(const puyoBoard& board, puyoPuyo& puyo) override;
    public :
        puyoPuyoFourWayMove(int amount, POSf delta);
        void act(puyoPuyo& puyo) override;
};