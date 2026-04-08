#pragma once

#include "puyoPuyoAct.hpp"


class puyoBoard;
class puyoPlayPuyo; 

class puyoPuyoDrop : public puyoPuyoAct
{
    private :
        bool test(puyoBoard& board,puyoPlayPuyo& puyo) override;
    public :
        puyoPuyoDrop(int amount);
        bool decline(puyoBoard& board,puyoPlayPuyo& puyo) override;
        void act(puyoPlayPuyo& puyo) override;
};