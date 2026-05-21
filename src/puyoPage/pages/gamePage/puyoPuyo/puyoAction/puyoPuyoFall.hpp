#pragma once

#include "puyoPuyoAct.hpp"

class puyoBoard;

class puyoPuyoFall : public puyoPuyoAct
{
    private :
        const puyoPuyo& puyo1, & puyo2;
        const puyoBoard& board;
    public :
        puyoPuyoFall(const puyoBoard& board, const puyoPuyo& puyo1, const puyoPuyo& puyo2);
        std::unique_ptr<puyoPuyoAct> clone() const override;
        bool decide(const puyoBoard& board, puyoPuyo& puyo) override;
        void act(puyoPuyo& puyo) override;
};