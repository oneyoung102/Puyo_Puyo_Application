#pragma once

#include "puyoPage/pages/gamePage/puyoPlayer/puyoBot/puyoBot.hpp"

class puyoBotModel1 : public puyoBot
{
    public :
        puyoBotModel1(POSi bsize, unsigned int act_time_unit = 0);      
        void think_perfect_lets(const puyoPlayer& player) override;
};