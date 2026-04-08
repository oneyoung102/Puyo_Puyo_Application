#pragma once

#include <tuple>
#include <vector>

#include "puyoPage/pages/gamePage/puyoBoard/puyoType.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"

class puyoBoard;

class puyoBoardGravityControll
{
    private :
        std::vector<puyoPuyo> gravity_puyos;
        bool gravity_puyo_is_out_in_board;

    public :
        puyoBoardGravityControll();

        void find(puyoBoard& board);
        void gravity(puyoBoard& board);
        void add(PUYO_INFO puyo);
        void add(std::vector<PUYO_INFO> puyos);
        std::vector<puyoPuyo>& get();

        bool empty();
        bool out();
};
