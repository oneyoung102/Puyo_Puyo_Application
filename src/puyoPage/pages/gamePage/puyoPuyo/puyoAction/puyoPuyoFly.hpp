#pragma once

#include "puyoPuyoAct.hpp"
#include "puyoPos.hpp"

class puyoBoard;
class puyoPuyo; 

class puyoPuyoFly : public puyoPuyoAct
{
    private :
        const POS dpos;
        void arrive(puyoPuyo& puyo) override;
    public :
        puyoPuyoFly(POS from_pos, POS to_pos, int amount);
        void act(puyoPuyo& puyo) override;
};