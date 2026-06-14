#pragma once

#include "puyoPage/pages/gamePage/puyoPhase/puyoMode/puyoMode.hpp"

class puyoModeBasic : public puyoMode
{
    public :
        puyoModeBasic();
        void proceed_mode(puyoPhase& phase, puyoPlayer& player) override;
};