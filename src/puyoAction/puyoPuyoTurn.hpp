#pragma once

#include "puyoPuyoAct.hpp"
#include <cmath>

using namespace std;

class puyoBoard;
class puyoPlayPuyo; 

class puyoPuyoTurn : public puyoPuyoAct
{
    private :
        puyoPuyoAct* sub_act;
        float degree;
        bool test_act(puyoBoard& board, puyoPlayPuyo& puyo) override;
        void arrive(puyoPlayPuyo& puyo, float x1,float y1,float x2,float y2) override;
    public :
        puyoPuyoTurn(int amount, float d);
        bool decline_act(puyoBoard& board,puyoPlayPuyo& puyo) override;
        void act_puyo(puyoPlayPuyo& puyo) override;
        void let_act() override;
};