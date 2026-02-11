#include "puyoPuyoAct.hpp"
#include "../puyoBoard.hpp"
#include "../puyoPuyo.hpp"
#include "puyoPuyoUp.hpp"

using namespace std;


bool puyoPuyoUp::test_act(puyoBoard& board, puyoPuyo& puyo)
{
    const auto[x1,y1,x2,y2] = puyo.get_puyo_pos();
    return !puyo.puyo_touched(board,x1,y1-dist) && !puyo.puyo_touched(board,x2,y2-dist);
}
puyoPuyoUp::puyoPuyoUp(int amount, float d) : puyoPuyoAct(amount){dist = d;}

void puyoPuyoUp::act_puyo(puyoPuyo& puyo)
{
    const auto[x1,y1,x2,y2] = puyo.get_puyo_pos();
    if(act_count == act_count_constant)
    {
        arrive(puyo,x1,y1,x2,y2);
        halt_act();
        return;
    }
    const float dy = -dist/act_count_constant;
    puyo.move_puyo(x1,y1+dy,x2,y2+dy);
    ++act_count;
}