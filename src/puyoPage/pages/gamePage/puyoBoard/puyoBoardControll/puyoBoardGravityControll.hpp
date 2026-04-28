#pragma once

#include <vector>

#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"

class puyoBoard;

class puyoBoardGravityControll
{
    private :
        std::vector<puyoPuyo> gravity_puyos;
        bool gravity_puyo_is_out_of_board;
    public :
        puyoBoardGravityControll();

        void gravity(puyoBoard& board);
        void add(const PUYO_INFO& puyo);
        void add(const std::vector<PUYO_INFO>& puyos);
        
        const std::vector<puyoPuyo>& get();

        bool empty() const;
        bool out() const;
};
