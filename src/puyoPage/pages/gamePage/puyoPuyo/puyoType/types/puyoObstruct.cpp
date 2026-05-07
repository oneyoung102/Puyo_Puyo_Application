#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/types/puyoObstruct.hpp"

using namespace std;

puyoObstruct::puyoObstruct()
    : _puyoType(Type::obstruct)
{}
std::unique_ptr<_puyoType> puyoObstruct::clone() const {return std::make_unique<puyoObstruct>();}

bool puyoObstruct::is_colored() const {return false;}
bool puyoObstruct::is_linkable(const _puyoType& other) const {return false;}