#pragma once

#include "puyoPuyoAct.hpp"


class puyoBoard;
class puyoPlayPuyo; 

class puyoPuyoDown : public puyoPuyoAct
{
    private :
        float dist;
        bool test(puyoBoard& board, puyoPlayPuyo& puyo) override;
    public :
        puyoPuyoDown(int amount, float dist);
        void act(puyoPlayPuyo& puyo)override;
};