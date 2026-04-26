#pragma once

#include "puyoPuyoAct.hpp"
#include "puyoPos.hpp"

class puyoBoard;
class puyoPlayPuyo; 

class puyoPuyoFourWayMove : public puyoPuyoAct
{
    private :
        const POS dpos;
        bool test(const puyoBoard& board, puyoPuyo& puyo) override;
    public :
        puyoPuyoFourWayMove(int amount, POS delta);
        void act(puyoPuyo& puyo) override;
};