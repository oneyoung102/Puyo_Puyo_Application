#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"

#include <utility>

using namespace std;

puyoPuyo::puyoPuyo(POSf pos, puyoType type, unique_ptr<puyoPuyoAct>&& act)
    : pos(pos)
    , type(type)
    , act(std::move(act))
{}
void puyoPuyo::move(POSf to_pos) {pos = to_pos;}

POSf const puyoPuyo::get_pos() const {return pos;}
puyoType puyoPuyo::get_type() const {return type;}

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

bool puyoPuyo::decide(const puyoBoard& board){return act && act->decide(board,*this);}
void puyoPuyo::act_let(){act->act(*this);}
void puyoPuyo::act_let(const puyoBoard& board)
{
    if(decide(board))
        act_let();
}

void puyoPuyo::set_act(unique_ptr<puyoPuyoAct>&& act){this->act = std::move(act);}
void puyoPuyo::set_act(){this->act = nullptr;}
void puyoPuyo::let()
{
    if(act)
        act->let();
}
