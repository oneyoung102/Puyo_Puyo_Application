#pragma once

#include "puyoPage/pages/gamePage/puyoPhase/puyoMode/puyoMode.hpp"
#include <vector>

class puyoModeBlocks : public puyoMode
{
    public :
        puyoModeBlocks(const std::vector<std::unique_ptr<puyoPlayer>>& players);
        void proceed_mode(puyoPhase& phase, const std::unique_ptr<puyoPlayer>&  player) override;
};