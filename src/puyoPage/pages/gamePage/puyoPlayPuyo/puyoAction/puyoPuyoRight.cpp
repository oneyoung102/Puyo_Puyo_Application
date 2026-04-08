#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoPuyoRight.hpp"

#include <cmath>

using namespace std;

bool puyoPuyoRight::test(puyoBoard& board, puyoPlayPuyo& puyo)
{
    const auto[x1,y1,x2,y2] = puyo.get_pos();
    return !puyo.touched(board,x1+dist,floor(y1)) && !puyo.touched(board,x2+dist,floor(y2)) && 
            !puyo.touched(board,x1+dist,ceil(y1)) && !puyo.touched(board,x2+dist,ceil(y2));
}
puyoPuyoRight::puyoPuyoRight(int amount, float dist) : puyoPuyoAct(amount){this->dist = dist;}

void puyoPuyoRight::act(puyoPlayPuyo& puyo)
{
    const auto[x1,y1,x2,y2] = puyo.get_pos();
    if(act_count == act_count_constant)
    {
        arrive(puyo,x1,y1,x2,y2);
        halt();
        return;
    }
    const float dx = dist/act_count_constant;
    puyo.move(x1+dx,y1,x2+dx,y2);
    ++act_count;
}