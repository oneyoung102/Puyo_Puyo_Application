#pragma once

#include <vector>

#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"

class puyoBoard;

class puyoGravityControll
{
    private :
        std::vector<puyoPuyo> gravity_puyos;
    public :
        puyoGravityControll();

        void gravity(puyoBoard& board);
        void add(puyoPuyo&& puyo);
        void add(std::vector<puyoPuyo>&& puyos);

        const std::vector<puyoPuyo>& view() const;

        bool empty() const;
};
