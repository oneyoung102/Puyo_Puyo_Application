#pragma once

#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include <vector>
class puyoBoard;

class puyoBoardObstructControll
{
    private :
        int obstruct_puyo, opposite_obstruct_puyo;
        bool approvement_spawn;
    public :
        puyoBoardObstructControll();
        void add(int count);
        std::vector<PUYO_INFO> to_gravity_puyo(puyoBoard& board, int obstruct_puyo_for_dropping);
        bool empty() const;
        const int& get() const;

        void add_opp(int count);
        int get_opp() const;
        bool empty_opp() const;
        void clear_opp();

        void approve_spawn();
        void disapprove_spawn();
        bool spawn_approved() const;
};