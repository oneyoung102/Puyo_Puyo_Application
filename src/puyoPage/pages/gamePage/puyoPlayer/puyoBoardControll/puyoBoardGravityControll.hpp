#pragma once

#include <vector>

#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"

class puyoBoard;

class puyoBoardGravityControll
{
    private :
        std::vector<puyoPuyo> gravity_puyos;
    public :
        puyoBoardGravityControll();

        void gravity(puyoBoard& board);
        void add(const puyoPuyo& puyo);
        void add(const std::vector<puyoPuyo>& puyos);
        
        const std::vector<puyoPuyo>& get() const;

        bool empty() const;
};
