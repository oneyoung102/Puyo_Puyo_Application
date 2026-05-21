#pragma once

#include "puyoPuyoAct.hpp"
#include "puyoTool/puyoPos.hpp"

class puyoBoard;
class puyoPlayPuyo; 

class puyoPuyoFourWayMove : public puyoPuyoAct
{
    private :
        const POSf dpos;
        bool test(const puyoBoard& board, puyoPuyo& puyo) override;
    public :
        puyoPuyoFourWayMove(int amount, POSf dpos);
        std::unique_ptr<puyoPuyoAct> clone() const override;
        void act(puyoPuyo& puyo) override;
};