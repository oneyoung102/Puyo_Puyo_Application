#pragma once

#include "puyoPuyoAct.hpp"
#include "../puyoBoard.hpp"
#include "../puyoPuyo.hpp"

using namespace std;

class puyoBoard;
class puyoPuyo; 

class puyoPuyoRight : public puyoPuyoAct
{
    private :
        float dist;
        bool test_act(puyoBoard& board, puyoPuyo& puyo) override;
        
    public :
        puyoPuyoRight(int amount, float d);

        void act_puyo(puyoPuyo& puyo) override;
};