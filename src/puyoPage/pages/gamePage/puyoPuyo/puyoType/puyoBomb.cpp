#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/puyoBomb.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include "puyoTool/puyoCast.hpp"

using namespace std;

puyoBomb::puyoBomb(typeState state, bool is_frozen, int bomb_tick_init, int bomb_tick)
    : puyoType(Type::bomb,state,is_frozen)
    , bomb_tick(bomb_tick)
    , bomb_tick_init(fmax(bomb_tick_init,1))
{}
std::unique_ptr<puyoType> puyoBomb::clone() const {return std::make_unique<puyoBomb>(state,__is_frozen,bomb_tick_init,bomb_tick);}
int puyoBomb::get_weight() const {return 1;}
bool puyoBomb::is_linkable(const puyoType& other) const {return false;}

void puyoBomb::update()
{
    ++bomb_tick;
    const float prop = CASTf(bomb_tick)/bomb_tick_init;
    if(prop < puyoGameConstant::BOMB_UPDATED1)
        state = typeState::explode_stay1;
    else if(prop < puyoGameConstant::BOMB_UPDATED2)
        state = typeState::explode_stay2;
    else if(prop < puyoGameConstant::BOMB_UPDATED3)
        state = typeState::explode_soon1;
    else if(prop < 1)
        state = typeState::explode_soon2;
    else
        state = typeState::exploded;
}