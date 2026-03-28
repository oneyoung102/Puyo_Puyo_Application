#pragma once

#include <vector>

#include "puyoPage/pages/gamePage/puyoTempPuyo/puyoGravityPuyo.hpp"

class puyoBoard;

class puyoBoardGravityControll
{
    private :
        std::vector<puyoGravityPuyo> gravity_puyos;
        bool gravity_puyo_is_out_in_board;
    public :
        puyoBoardGravityControll();

        void find_gravity_puyo(puyoBoard& board);
        void gravity_gravity_puyos(puyoBoard& board);
        void push_gravity_puyo(puyoGravityPuyo&& ptp);
        void push_gravity_puyo(std::vector<puyoGravityPuyo>&& ptp_v);
        std::vector<puyoGravityPuyo>& get_gravity_puyos();

        bool gravity_puyo_empty();
        bool gravity_puyo_is_out();
};
