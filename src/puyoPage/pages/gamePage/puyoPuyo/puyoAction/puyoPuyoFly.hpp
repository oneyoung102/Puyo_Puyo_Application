#pragma once

#include "puyoPuyoAct.hpp"
#include "puyoPos.hpp"

class puyoBoard;
class puyoPuyo; 

class puyoPuyoFly : public puyoPuyoAct
{
    private :
        const POSf dpos, from_pos;
        void arrive(puyoPuyo& puyo) override;
    public :
        puyoPuyoFly(POSf from_pos, POSf to_pos, int amount);
        void act(puyoPuyo& puyo) override;
};