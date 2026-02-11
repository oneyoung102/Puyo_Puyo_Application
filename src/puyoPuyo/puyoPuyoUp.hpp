#pragma once

#include "puyoPuyoAct.hpp"
#include "../puyoBoard.hpp"
#include "../puyoPuyo.hpp"

using namespace std;

class puyoBoard;
class puyoPuyo; 

class puyoPuyoUp : public puyoPuyoAct
{
    private :
        float start_x1,start_y1,start_x2,start_y2;
        float dist;
        bool test_act(puyoBoard& board, puyoPuyo& puyo) override;
    public :
        puyoPuyoUp(int amount, float d);

        void act_puyo(puyoPuyo& puyo) override;
};