#pragma once

#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include <vector>

class puyoBoard;
class puyoPlayPuyo;

class puyoBoardFutureControll
{
    private :
        std::vector<puyoPuyo> future_puyos;
    public :
        puyoBoardFutureControll();
        void update(const puyoBoard& board, const puyoPlayPuyo& play_puyo);
        void fall(const puyoBoard& board);

        const std::vector<puyoPuyo>& get() const;
        
};