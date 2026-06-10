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
        std::vector<puyoPuyo> to_gravity_puyo(puyoBoard& board, int obstruct_puyo_for_dropping);
        bool empty() const;
        
        const int& get() const;

        void add_opposite(int count);
        int get_opposite() const;
        bool empty_opposite() const;
        void clear_opposite();

        void approve_spawn();
        void disapprove_spawn();
        bool spawn_approved() const;
};