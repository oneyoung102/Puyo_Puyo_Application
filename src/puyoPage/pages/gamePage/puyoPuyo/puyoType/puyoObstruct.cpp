#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/puyoObstruct.hpp"

using namespace std;

puyoObstruct::puyoObstruct(bool is_frozen)
    : puyoType(Type::obstruct,State::none,is_frozen)
{}
std::unique_ptr<puyoType> puyoObstruct::clone() const {return std::make_unique<puyoObstruct>(__is_frozen);}
int puyoObstruct::get_weight() const {return 0;}

bool puyoObstruct::is_linkable(const puyoType& other) const {return false;}