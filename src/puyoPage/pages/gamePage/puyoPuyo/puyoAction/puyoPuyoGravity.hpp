#pragma once

#include "puyoPuyoAct.hpp"

class puyoBoard;
class puyoPuyo; 

class puyoPuyoGravity : public puyoPuyoAct
{
    private :
        bool test(const puyoBoard& board, puyoPuyo& puyo) override;
        void arrive(puyoPuyo& puyo) override;
    public :
        puyoPuyoGravity(int amount);
        std::unique_ptr<puyoPuyoAct> clone() const override;
        bool decide(const puyoBoard& board,puyoPuyo& puyo) override;
        void act(puyoPuyo& puyo) override;
};