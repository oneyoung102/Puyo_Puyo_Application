#include "../puyoBoard.hpp"
#include "../puyoPlayPuyo.hpp"
#include "puyoPuyoDown.hpp"

#include <cmath>

using namespace std;


bool puyoPuyoDown::test_act(puyoBoard& board, puyoPlayPuyo& puyo)
{
    const auto[x1,y1,x2,y2] = puyo.get_puyo_pos();
    return !puyo.puyo_touched(board,x1,ceil(y1)+dist) && !puyo.puyo_touched(board,x2,ceil(y2)+dist);
}

puyoPuyoDown:: puyoPuyoDown(int amount, float d) : puyoPuyoAct(amount){dist = d;};

void puyoPuyoDown::act_puyo(puyoPlayPuyo& puyo)
{
    const auto[x1,y1,x2,y2] = puyo.get_puyo_pos();
    if(act_count == act_count_constant)
    {
        arrive(puyo,x1,y1,x2,y2);
        halt_act();
        return;
    }
    const float dy = dist/act_count_constant;
    puyo.move_puyo(x1,y1+dy,x2,y2+dy);
    ++act_count;
};