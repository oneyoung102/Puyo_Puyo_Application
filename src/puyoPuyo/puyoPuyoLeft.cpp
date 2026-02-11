#include "puyoPuyoAct.hpp"
#include "../puyoBoard.hpp"
#include "../puyoPuyo.hpp"
#include "puyoPuyoLeft.hpp"

using namespace std;

bool puyoPuyoLeft::test_act(puyoBoard& board, puyoPuyo& puyo)
{
    const auto[x1,y1,x2,y2] = puyo.get_puyo_pos();
    return !puyo.puyo_touched(board,x1-dist,y1) && !puyo.puyo_touched(board,x2-dist,y2);
}

puyoPuyoLeft::puyoPuyoLeft(int amount, float d) : puyoPuyoAct(amount){dist = d;}

void puyoPuyoLeft::act_puyo(puyoPuyo& puyo)
{
    const auto[x1,y1,x2,y2] = puyo.get_puyo_pos();
    if(act_count == act_count_constant)
    {
        arrive(puyo,x1,y1,x2,y2);
        halt_act();
        return;
    }
    const float dx = -dist/act_count_constant;
    puyo.move_puyo(x1+dx,y1,x2+dx,y2);
    ++act_count;
};
