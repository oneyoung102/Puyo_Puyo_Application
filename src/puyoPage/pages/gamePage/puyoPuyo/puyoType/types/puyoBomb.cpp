#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/types/puyoBomb.hpp"
#include "puyoTool/puyoCast.hpp"

using namespace std;

puyoBomb::puyoBomb(int bomb_tick_init, int bomb_tick)
    : _puyoType(Type::bomb)
    , bomb_tick(bomb_tick)
    , bomb_tick_init(fmax(bomb_tick_init,1))
{}
std::unique_ptr<_puyoType> puyoBomb::clone() const {return std::make_unique<puyoBomb>(bomb_tick_init,bomb_tick);}
bool puyoBomb::is_colored() const {return true;}
bool puyoBomb::is_linkable(const _puyoType& other) const {return false;}

float puyoBomb::get_bomb_state() const {return CASTf(bomb_tick)/bomb_tick_init;}
void puyoBomb::proceed_bomb() {if(bomb_tick > 0) --bomb_tick;}
bool puyoBomb::is_exploded() const {return bomb_tick == 0;}