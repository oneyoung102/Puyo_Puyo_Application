#pragma once

#include "puyoPuyoAct.hpp"

class puyoBoard;
class puyoPuyo; 

class puyoPuyoVanish : public puyoPuyoAct
{
    private :
        float dist;
    public :
        puyoPuyoVanish(int amount);
        void act(puyoPuyo& puyo) override;
};