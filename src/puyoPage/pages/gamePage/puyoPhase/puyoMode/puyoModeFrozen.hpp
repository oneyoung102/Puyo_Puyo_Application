#pragma once

#include "puyoPage/pages/gamePage/puyoPhase/puyoMode/puyoMode.hpp"
#include <random>
#include <vector>

class puyoModeFrozen : public puyoMode
{
    private :
        std::vector<int> time;
        std::mt19937 gen;
    public :
        puyoModeFrozen(int player_count);
        void proceed_mode(puyoPhase& phase, puyoPlayer& player) override;
};