#pragma once

#include "puyoPuyoAct.hpp"
#include "../puyoBoard.hpp"
#include "../puyoPuyo.hpp"

using namespace std;

class puyoBoard;
class puyoPuyo; 

class puyoPuyoFall : public puyoPuyoAct
{
    private :
        float dist;
        bool test_act(puyoBoard& board, puyoPuyo& puyo) override;
    public :
        puyoPuyoFall(int amount, float d);

        bool decline_act(puyoBoard& board, puyoPuyo& puyo) override;
        void act_puyo(puyoPuyo& puyo) override;
};