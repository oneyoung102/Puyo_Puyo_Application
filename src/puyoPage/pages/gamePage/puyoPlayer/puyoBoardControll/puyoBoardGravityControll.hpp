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
        void add(const PUYO_INFO& puyo);
        void add(const std::vector<PUYO_INFO>& puyos);
        
        const std::vector<puyoPuyo>& get() const;

        bool empty() const;
};
