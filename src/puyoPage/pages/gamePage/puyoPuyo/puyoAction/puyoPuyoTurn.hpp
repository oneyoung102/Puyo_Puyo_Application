#pragma once

#include "puyoPuyoAct.hpp"
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
        Direction dir;
        const float rad, c, s;
        puyoPuyo& center;

        std::array<std::unique_ptr<puyoPuyoAct>,2> sub_acts;
        bool test(puyoBoard& board, puyoPuyo& puyo) override;
        void arrive(puyoPuyo& puyo) override;
    public :
        puyoPuyoTurn(int amount, puyoPuyo& center, std::pair<float,float> turning);
        bool decline(puyoBoard& board,puyoPuyo& puyo) override;
        void act(puyoPuyo& puyo) override;
};