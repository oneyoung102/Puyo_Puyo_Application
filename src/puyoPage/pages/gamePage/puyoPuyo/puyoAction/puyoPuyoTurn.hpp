#pragma once

#include "puyoPage/pages/gamePage/puyoPuyo/puyoAction/puyoPuyoFourWayMove.hpp"
#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include <memory>


class puyoBoard;

class puyoPuyoTurn : public puyoPuyoAct
{
    private :
        enum class Direction
        {
            UP,
            RIGHT,
            DOWN,
            LEFT
        };
        Direction turn_dir;
        const float rad, c, s;
        puyoPuyo& center;

        std::array<std::unique_ptr<puyoPuyoFourWayMove>,2> sub_acts;
        bool test(const puyoBoard& board, puyoPuyo& puyo) override;
        void arrive(puyoPuyo& puyo) override;
    public :
        puyoPuyoTurn(int amount, puyoPuyo& center, POS turning);
        void act(puyoPuyo& puyo) override;
};