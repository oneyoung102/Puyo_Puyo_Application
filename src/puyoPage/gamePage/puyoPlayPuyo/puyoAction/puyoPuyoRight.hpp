#pragma once

#include "puyoPuyoAct.hpp"

using namespace std;

class puyoBoard;
class puyoPlayPuyo; 

class puyoPuyoRight : public puyoPuyoAct
{
    private :
        float dist;
        bool test_act(puyoBoard& board, puyoPlayPuyo& puyo) override;
        
    public :
        puyoPuyoRight(int amount, float d);

        void act_puyo(puyoPlayPuyo& puyo) override;
};