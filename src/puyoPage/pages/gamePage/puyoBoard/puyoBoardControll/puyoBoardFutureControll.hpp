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
        void find(puyoBoard& board, puyoPlayPuyo& puyo);
        void kill();
    
        std::vector<puyoPuyo>& get();
        
};