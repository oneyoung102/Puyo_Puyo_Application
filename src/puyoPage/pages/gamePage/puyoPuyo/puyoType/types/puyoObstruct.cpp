#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/types/puyoObstruct.hpp"

using namespace std;

puyoObstruct::puyoObstruct(bool is_frozen)
    : _puyoType(Type::obstruct,typeState::none,is_frozen)
{}
std::unique_ptr<_puyoType> puyoObstruct::clone() const {return std::make_unique<puyoObstruct>(_is_frozen);}

bool puyoObstruct::is_colored() const {return false;}
bool puyoObstruct::is_linkable(const _puyoType& other) const {return false;}