#pragma once

#include "puyoPuyoAct.hpp"

using namespace std;

class puyoBoard;
class puyoPlayPuyo; 

class puyoPuyoDrop : public puyoPuyoAct
{
    private :
        bool test_act(puyoBoard& board,puyoPlayPuyo& puyo) override;
    public :
        puyoPuyoDrop(int amount);
        bool decline_act(puyoBoard& board,puyoPlayPuyo& puyo) override;
        void act_puyo(puyoPlayPuyo& puyo) override;
};