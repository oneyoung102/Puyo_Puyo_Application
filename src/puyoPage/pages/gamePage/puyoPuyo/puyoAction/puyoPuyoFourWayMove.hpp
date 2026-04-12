#pragma once

#include "puyoPuyoAct.hpp"
#include <utility>


class puyoBoard;
class puyoPlayPuyo; 

class puyoPuyoFourWayMove : public puyoPuyoAct
{
    private :
        const int dx, dy;
        bool test(puyoBoard& board, puyoPuyo& puyo) override;
    public :
        puyoPuyoFourWayMove(int amount, std::pair<float,float> delta);
        void act(puyoPuyo& puyo) override;
};