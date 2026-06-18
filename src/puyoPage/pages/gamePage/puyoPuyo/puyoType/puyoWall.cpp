#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/puyoWall.hpp"

using namespace std;

puyoWall::puyoWall(bool is_frozen)
    : puyoType(Type::wall,typeState::none,is_frozen)
{}
std::unique_ptr<puyoType> puyoWall::clone() const {return std::make_unique<puyoWall>(__is_frozen);}
int puyoWall::get_weight() const {return 0;}

bool puyoWall::is_linkable(const puyoType& other) const {return false;}
bool puyoWall::is_gravityable() const {return false;}

void puyoWall::freeze() {return;} //얼릴 수 없음