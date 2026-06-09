#pragma once

#include "puyoPage/pages/gamePage/puyoPhase/puyoMode/puyoMode.hpp"
#include "puyoPage/pages/gamePage/puyoPlayer/puyoBoardControll/puyoBoardVanishControll.hpp"
#include <random>

class puyoModeCharged : public puyoMode
{
    private :
        std::mt19937 gen;
    public :
        puyoModeCharged(const std::vector<std::unique_ptr<puyoPlayer>>& players);
        void proceed_mode(puyoPhase& phase, const std::unique_ptr<puyoPlayer>& player) override;
};