#pragma once

#include "puyoPuyoAct.hpp"
#include "../puyoBoard.hpp"
#include "../puyoPuyo.hpp"
#include <cmath>

using namespace std;

class puyoBoard;
class puyoPuyo; 

class puyoPuyoTurn : public puyoPuyoAct
{
    private :
        puyoPuyoAct* sub_act;
        float degree;
        bool test_act(puyoBoard& board, puyoPuyo& puyo) override;
        void arrive(puyoPuyo& puyo, float x1,float y1,float x2,float y2) override;
    public :
        puyoPuyoTurn(int amount, float d);
        bool decline_act(puyoBoard& board,puyoPuyo& puyo) override;
        void act_puyo(puyoPuyo& puyo) override;
        void let_act() override;
};