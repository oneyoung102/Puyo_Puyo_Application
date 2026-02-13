#pragma once

#include "puyoPuyoAct.hpp"

using namespace std;

class puyoBoard;
class puyoPlayPuyo; 

class puyoPuyoGravity : public puyoPuyoAct
{
    private :
        float dist;
        void arrive(puyoPlayPuyo& puyo, float x1,float y1,float x2,float y2) override;
        bool test_act(puyoBoard& board, puyoPlayPuyo& puyo) override;
    public :
        puyoPuyoGravity(int amount, float d);

        bool decline_act(puyoBoard& board, puyoPlayPuyo& puyo) override;
        void act_puyo(puyoPlayPuyo& puyo) override;
};