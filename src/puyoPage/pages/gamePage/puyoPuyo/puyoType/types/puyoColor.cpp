#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/types/puyoColor.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"

using namespace std;

puyoColor::puyoColor(Type color, bool is_frozen, bool charged)
    : _puyoType(
        Type::red <= color && color <= Type::pupple
        ? color
        : throw runtime_error("Invalid color"), typeState::none,is_frozen)
    , charged(charged)
{}
const vector<_puyoType::Type> puyoColor::links = {_puyoType::Type::obstruct};

std::unique_ptr<_puyoType> puyoColor::clone() const {return std::make_unique<puyoColor>(this->type,_is_frozen,charged);}
int puyoColor::get_weight() const {return charged ? puyoGameConstant::CHARGED_COLOR_PUYO_WEIGHT : 1;}
bool puyoColor::is_colored() const {return true;}

bool puyoColor::is_linkable(const _puyoType& other) const
{
    if(other.is_colored())
        return is_same(other);
    for(const auto link : links)
        if(other.get() == link)
            return true;
    return false;
}

void puyoColor::charge() {charged = true;}
void puyoColor::uncharge() {charged = false;}
bool puyoColor::is_charged() const {return charged;}