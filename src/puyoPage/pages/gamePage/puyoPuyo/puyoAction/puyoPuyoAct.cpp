#include "puyoPuyoAct.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include "puyoTool/puyoCast.hpp"
#include <stdexcept>

void puyoPuyoAct::arrive(puyoPuyo& puyo)
{
    const auto[x,y] = puyo.get_pos();
    puyo.move({round(x),y});
}
bool puyoPuyoAct::test(const puyoBoard& board, puyoPuyo& puyo){return true;}

bool puyoPuyoAct::decide(const puyoBoard& board, puyoPuyo& puyo)
{
    if(act_count == 0)
    {
        if(test(board, puyo))
            return true;
    }
    else if(acting())
        return true;
    else
        arrive(puyo);
    halt();
    return false;
}
puyoPuyoAct::puyoPuyoAct(int amount)
    : act_count_init(amount)
    , halted(-1)
    , act_count(halted)
{}

void puyoPuyoAct::let(int amount)
{
    if(!acting())
    {
        if(amount < halted)
            throw std::runtime_error("When letting, act count is smaller than 'halted'");
        act_count = amount;
    }
}
bool puyoPuyoAct::acting() const {return halted < act_count && act_count < act_count_init;}
void puyoPuyoAct::halt(){act_count = halted;}
float puyoPuyoAct::get_state() const {return CASTf(act_count)/act_count_init;}
int puyoPuyoAct::get_act_count_init() const {return act_count_init;}
