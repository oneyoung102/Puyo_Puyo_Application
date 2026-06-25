#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/puyoWater.hpp"

using namespace std;

puyoWater::puyoWater(bool is_frozen)
    : puyoType(puyoType::Type::water, State::can_water,is_frozen)
{}

std::unique_ptr<puyoType> puyoWater::clone() const {return std::make_unique<puyoWater>(__is_frozen);}
int puyoWater::get_weight() const {return 0;}

bool puyoWater::is_linkable(const puyoType& other) const {return false;}

void puyoWater::update()
{
    if(this->is_frozen())
        state = puyoType::State::none;
    else
        state = puyoType::State::can_water;
}