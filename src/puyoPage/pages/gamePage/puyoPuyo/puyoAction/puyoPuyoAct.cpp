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
    {
        if(act_count == act_count_init)
            arrive(puyo);
        return true;
    }
    halt();
    return false;
}

bool puyoPuyoAct::acting(){return 0 <= act_count && act_count <= act_count_init;}
puyoPuyoAct::puyoPuyoAct(int amount) : act_count_init(amount){act_count = -1;}
void puyoPuyoAct::let()
{
    if(!acting())
        act_count = 0;
}
void puyoPuyoAct::halt(){act_count = -1;}
float puyoPuyoAct::get_state(){return CASTf(act_count)/act_count_init;}
int puyoPuyoAct::get_act_count_init(){return act_count_init;}
