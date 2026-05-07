#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/types/puyoColor.hpp"

using namespace std;

puyoColor::puyoColor(Type color, bool is_frozen)
    : _puyoType(
        Type::red <= color && color <= Type::pupple
        ? color
        : throw runtime_error("Invalid color"), is_frozen)
{}
const vector<_puyoType::Type> puyoColor::links = {_puyoType::Type::obstruct};

std::unique_ptr<_puyoType> puyoColor::clone() const {return std::make_unique<puyoColor>(this->type,_is_frozen);}
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