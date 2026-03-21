#include "puyoPage/pages/gamePage/puyoPhase/puyoMode/puyoModeAcceleration.hpp"

#include "puyoPage/pages/gamePage/puyoPhase/puyoPhase.hpp"

puyoModeAcceleration::puyoModeAcceleration(int init_gravity_value)
    : gravity_init(init_gravity_value)
    , gravity_delta(max(init_gravity_value/40,1))
    , gravity_min(init_gravity_value/4)
{}
void puyoModeAcceleration::proceed_mode(puyoPhase& phase)
{
    if(gravity_init - gravity_delta <= gravity_min)
        return;
    for(auto&& player : phase.get_players())
        if(player->get_puyo().is_dropped())
        {
            phase.set_gravity_value(gravity_init -= gravity_delta);
            break;
        }
}