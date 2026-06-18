#include "puyoPage/pages/gamePage/puyoPhase/puyoMode/puyoModeCharged.hpp"

#include "puyoPage/pages/gamePage/puyoPhase/puyoPhase.hpp"
#include "puyoPage/pages/gamePage/puyoPlayer/puyoPlayer.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include <random>

using namespace std;
using namespace puyoGameConstant;

puyoModeCharged::puyoModeCharged(std::vector<puyoPlayer>& players)
    : gen(random_device{}())
{
    for(auto& player : players)
        player.controll_vanish().set_condition(CHARGED_COLOR_PUYO_WEIGHT+1); //차지 뿌요 혼자 터지는 걸 방지를 위해 +1
}
void puyoModeCharged::proceed_mode(puyoPhase& phase, puyoPlayer& player)
{
    const int puyo_count = player.get_new_puyo_count();
    auto& new_types = phase.get_new_puyos().refer(puyo_count+DISPLAYED_NEXT_PUYO_COUNT-1);
    if(new_types[0].is_charged() || new_types[1].is_charged())
        return;
    if(puyo_count%CHARGE_CYCLE != 0)
        return;
    uniform_int_distribution<> dist(0,99);
    const int prob = dist(gen);
    if(prob < 50)  
        new_types[0].charge();
    else
        new_types[1].charge();
}