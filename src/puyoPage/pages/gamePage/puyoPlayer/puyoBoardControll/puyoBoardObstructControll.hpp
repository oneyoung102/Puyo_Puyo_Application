#pragma once

#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include <vector>
class puyoBoard;

class puyoBoardObstructControll
{
    private :
        int obstruct_puyo, accumulated_score;
        bool approvement_spawn;
    public :
        puyoBoardObstructControll();
        void add(int count);
        std::vector<puyoPuyo> to_gravity_puyo(puyoBoard& board, int obstruct_puyo_for_dropping);
        bool empty() const;
        
        const int& get() const;

        void accumulate_score(int score);
        int get_accumulated_score() const;
        void clear_accumulated_score();

        void approve_spawn();
        void disapprove_spawn();
        bool spawn_approved() const;
};