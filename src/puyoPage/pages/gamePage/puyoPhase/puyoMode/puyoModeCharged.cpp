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
    auto& new_types = phase.get_new_types()[player.get_new_puyo_count()+DISPLAYED_NEXT_PUYO_COUNT-1];
    if(new_types.first.is_charged() || new_types.second.is_charged())
        return;
    if(player.get_new_puyo_count()%CHARGE_CYCLE != 0)
        return;
    uniform_int_distribution<> dist(0,99);
    const int prob = dist(gen);
    if(prob < 50)  
        new_types.first.charge();
    else
        new_types.second.charge();
}