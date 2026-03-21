#pragma once

#include "puyoPage/pages/gamePage/puyoPhase/puyoMode/puyoMode.hpp"

class puyoModeAcceleration : public puyoMode
{
    private :
        int gravity_init;
        const int gravity_delta, gravity_min;
    public :
        puyoModeAcceleration(int init_gravity_value);
        void proceed_mode(puyoPhase& phase) override;
};