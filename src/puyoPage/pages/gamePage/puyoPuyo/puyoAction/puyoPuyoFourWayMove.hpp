#pragma once

#include "puyoPuyoAct.hpp"


class puyoBoard;
class puyoPlayPuyo; 

class puyoPuyoFourWayMove : public puyoPuyoAct
{
    private :
        const int dx, dy;
        bool test(puyoBoard& board, puyoPuyo& puyo) override;
    public :
        puyoPuyoFourWayMove(int amount, int dx, int dy);
        void act(puyoPuyo& puyo) override;
};