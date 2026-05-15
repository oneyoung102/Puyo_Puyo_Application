#include "puyoPage/pages/gamePage/puyoPhase/puyoMode/puyoModeSpeed.hpp"

#include "puyoPage/pages/gamePage/puyoPhase/puyoPhase.hpp"
#include "puyoPage/pages/gamePage/puyoPlayer/puyoPlayer.hpp"

puyoModeSpeed::puyoModeSpeed(int init_gravity_value)
    : gravity_init(init_gravity_value)
    , gravity_delta(fmax(init_gravity_value/100,1))
    , gravity_min(init_gravity_value/4)
{}
void puyoModeSpeed::proceed_mode(puyoPhase& phase, const std::unique_ptr<puyoPlayer>& player)
{
    if(gravity_init - gravity_delta <= gravity_min)
        return;
    if(player->get_puyo().dropped(player->get_board()))
    {
        phase.set_gravity_value(gravity_init -= gravity_delta);
        phase.set_signal(puyoModeSignal::speed_up);
    }
}