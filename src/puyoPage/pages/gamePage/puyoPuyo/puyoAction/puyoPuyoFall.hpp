#pragma once

#include "puyoPuyoAct.hpp"
#include <array>


class puyoBoard;

class puyoPuyoFall : public puyoPuyoAct
{
    private :
        const puyoPuyo& puyo1, & puyo2;
        const puyoBoard& board;
    public :
        puyoPuyoFall(const puyoBoard& board, const puyoPuyo& puyo1, const puyoPuyo& puyo2);
        bool decide(const puyoBoard& board, puyoPuyo& puyo) override;
        void act(puyoPuyo& puyo) override;
};