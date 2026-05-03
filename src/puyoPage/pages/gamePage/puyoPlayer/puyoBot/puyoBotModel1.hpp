#pragma once

#include "puyoPage/pages/gamePage/puyoPlayer/puyoBot/puyoBot.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"

class puyoBotModel1 : public puyoBot
{
    public :
        puyoBotModel1(POSi bsize, unsigned int act_time_unit = 0);      
        void think_perfect_lets(const puyoBoard& board, const puyoPlayPuyo& puyo) override;
};