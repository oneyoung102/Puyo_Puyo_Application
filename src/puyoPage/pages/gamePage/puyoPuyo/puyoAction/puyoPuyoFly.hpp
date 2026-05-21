#pragma once

#include "puyoPuyoAct.hpp"
#include "puyoTool/puyoPos.hpp"

class puyoBoard;
class puyoPuyo; 

class puyoPuyoFly : public puyoPuyoAct
{
    private :
        const POSf dpos, from_pos;
        void arrive(puyoPuyo& puyo) override;
    public :
        puyoPuyoFly(int amount, const POSf& from_pos, const POSf& dpos);
        std::unique_ptr<puyoPuyoAct> clone() const override;
        void act(puyoPuyo& puyo) override;
};