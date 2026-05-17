#include "puyoPuyoAct.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include "puyoTool/puyoCast.hpp"

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

bool puyoPuyoAct::acting(){return halted < act_count && act_count < act_count_init;}
puyoPuyoAct::puyoPuyoAct(int amount)
    : act_count_init(amount)
    , halted(-1)
    , act_count(halted)
{}
void puyoPuyoAct::let()
{
    if(!acting())
        act_count = 0;
}
void puyoPuyoAct::halt(){act_count = halted;}
float puyoPuyoAct::get_state(){return CASTf(act_count)/act_count_init;}
int puyoPuyoAct::get_act_count_init(){return act_count_init;}
