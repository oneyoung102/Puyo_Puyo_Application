#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"

#include <utility>

using namespace std;

puyoPuyo::puyoPuyo(float x, float y, puyoType type, unique_ptr<puyoPuyoAct_temp>&& act)
{  
    this->x = x;
    this->y = y;
    this->type = type;
    this->act = std::move(act);
}
puyoPuyo::puyoPuyo(float x, float y, puyoType type)
{
    this->x = x;
    this->y = y;
    this->type = type;
    this->act = nullptr;
}
bool puyoPuyo::touched(puyoBoard& board, int ix, int iy)
{
    return iy >= 0 && (!board.in(iy,ix) || board.get_puyo(iy,ix) != puyoType::blank)
        || iy < 0 && !board.in_col(ix);
}
void puyoPuyo::move(float to_x, float to_y)
{
    x = to_x;
    y = to_y;
}

pair<float,float> puyoPuyo::get_pos(){return make_pair(x,y);}
puyoType puyoPuyo::get_type(){return type;}
int puyoPuyo::get_tick(){return act->get_act_count_init();}


bool puyoPuyo::acting(){return act->acting();}
float puyoPuyo::get_state(){return act->get_state();}
void puyoPuyo::act_let(puyoBoard& board)
{
    if(act->decline(board,*this))
        act->act(*this);
}
void puyoPuyo::change_act(unique_ptr<puyoPuyoAct_temp>&& act){this->act = std::move(act);}
void puyoPuyo::let(){act->let();}
