#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoPuyoUp.hpp"

using namespace std;


bool puyoPuyoUp::test(puyoBoard& board, puyoPlayPuyo& puyo)
{
    const auto[x1,y1,x2,y2] = puyo.get_pos();
    return !puyo.touched(board,x1,y1-dist) && !puyo.touched(board,x2,y2-dist);
}
puyoPuyoUp::puyoPuyoUp(int amount, float dist) : puyoPuyoAct(amount){this->dist = dist;} 

void puyoPuyoUp::act(puyoPlayPuyo& puyo)
{
    const auto[x1,y1,x2,y2] = puyo.get_pos();
    if(act_count == act_count_constant)
    {
        arrive(puyo,x1,y1,x2,y2);
        halt();
        return;
    }
    const float dy = -dist/act_count_constant;
    puyo.move(x1,y1+dy,x2,y2+dy);
    ++act_count;
}