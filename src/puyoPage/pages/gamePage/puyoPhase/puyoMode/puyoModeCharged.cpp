#include "puyoPage/pages/gamePage/puyoPhase/puyoMode/puyoModeCharged.hpp"

#include "puyoPage/pages/gamePage/puyoPhase/puyoPhase.hpp"
#include "puyoPage/pages/gamePage/puyoPlayer/puyoPlayer.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include <random>

using namespace std;
using namespace puyoGameConstant;

puyoModeCharged::puyoModeCharged(int play_count)
    : time(max(play_count,0),0)
    , gen(random_device{}())
{}
void puyoModeCharged::proceed_mode(puyoPhase& phase, const std::unique_ptr<puyoPlayer>& player)
{
    player->controll_vanish().set_condition(CHARGED_COLOR_PUYO_WEIGHT+1); //차지 뿌요 혼자 터지는 걸 방지

    const int player_num = player->get_player_num();
    ++time[player_num];
    if(time[player_num] < CHARGE_TICK)
        return;
    time[player_num] = 0;

    if(phase.get_new_types().back().first == phase.get_new_types().back().second)
        return;
    uniform_int_distribution<> dist(0,99);
    const int prob = dist(gen);
    if(prob < PROB_CHARGE_ONCE)  
        phase.get_new_types().back().first.charge();
    if(PROB_CHARGE_ONCE-PROB_CHARGE_TWICE <= prob && prob < 2*PROB_CHARGE_ONCE-PROB_CHARGE_TWICE)
        phase.get_new_types().back().second.charge();
}