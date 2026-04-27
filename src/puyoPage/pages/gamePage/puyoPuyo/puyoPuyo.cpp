#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"

#include <utility>

using namespace std;

puyoPuyo::puyoPuyo(POSf pos, puyoType type, unique_ptr<puyoPuyoAct>&& act)
{  
    this->pos = pos;
    this->type = type;
    this->act = std::move(act);
}
puyoPuyo::puyoPuyo(POSf pos, puyoType type)
{
    this->pos = pos;
    this->type = type;
    this->act = nullptr;
}

void puyoPuyo::move(POSf to_pos) {pos = to_pos;}

POSf const puyoPuyo::get_pos() const {return pos;}
puyoType const puyoPuyo::get_type() const {return type;}

int const puyoPuyo::get_tick() const
{
    if(act)
        return act->get_act_count_init();
    return -1;
}
float const puyoPuyo::get_state() const
{
    if(act)
        return act->get_state();
    return -1.0;
}

bool const puyoPuyo::acting() const {return act && act->acting();}
bool puyoPuyo::have_act() const {return act != nullptr;}
void puyoPuyo::act_let(const puyoBoard& board)
{
    if(act && act->decide(board,*this))
        act->act(*this);
}
void puyoPuyo::set_act(unique_ptr<puyoPuyoAct>&& act){this->act = std::move(act);}
void puyoPuyo::set_act(){this->act = nullptr;}
void puyoPuyo::let()
{
    if(act)
        act->let();
}
