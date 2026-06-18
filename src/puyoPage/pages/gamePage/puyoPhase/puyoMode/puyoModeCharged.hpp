#pragma once

#include "puyoPage/pages/gamePage/puyoPhase/puyoMode/puyoMode.hpp"
#include <random>

class puyoModeCharged : public puyoMode
{
    private :
        std::mt19937 gen;
    public :
        puyoModeCharged(std::vector<puyoPlayer>& players);
        void proceed_mode(puyoPhase& phase, puyoPlayer& player) override;
};