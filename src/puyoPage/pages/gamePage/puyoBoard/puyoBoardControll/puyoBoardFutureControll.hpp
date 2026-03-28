#pragma once

#include "puyoPage/pages/gamePage/puyoTempPuyo/puyoFuturePuyo.hpp"
#include <vector>

class puyoBoard;
class puyoPlayPuyo;

class puyoBoardFutureControll
{
    private :
        std::vector<puyoFuturePuyo> future_puyos;
    public :
        puyoBoardFutureControll();
        void find_future_puyos(puyoBoard& board, puyoPlayPuyo& puyo);
        void remove_future_puyos();
    
        std::vector<puyoFuturePuyo>& get_future_puyos();
        
};