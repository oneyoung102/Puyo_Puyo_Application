#pragma once

#include "puyoPage/pages/gamePage/puyoPhase/puyoMode/puyoMode.hpp"

class puyoModeSpeed : public puyoMode
{
    private :
        int gravity_init;
        const int gravity_delta, gravity_min;
    public :
        puyoModeSpeed(int init_gravity_value);
        void proceed_mode(puyoPhase& phase, const puyoPlayer& player) override;
};