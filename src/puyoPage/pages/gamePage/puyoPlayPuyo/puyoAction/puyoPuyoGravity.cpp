#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoPuyoGravity.hpp"

using namespace std;

puyoPuyoGravity::puyoPuyoGravity(int amount, float dist): puyoPuyoAct(amount)
{
    this->dist = dist;
    act_count = 0;
}
bool puyoPuyoGravity::test(puyoBoard& board, puyoPlayPuyo& puyo)
{
    const auto[x1,y1,x2,y2] = puyo.get_pos();
    return !puyo.touched(board,x1,y1+1) && !puyo.touched(board,x2,y2+1);
}
bool puyoPuyoGravity::decline(puyoBoard& board, puyoPlayPuyo& puyo)
{
    const auto[x1,y1,x2,y2] = puyo.get_pos();
    if(test(board, puyo))
    {
        if(!acting())
            let();
        return true;
    }
    else
    {
        halt();
        return false;
    }
    return false;
}
void puyoPuyoGravity::act(puyoPlayPuyo& puyo)
{
    if(act_count == act_count_constant)
        act_count = 0;
    const auto[x1,y1,x2,y2] = puyo.get_pos();
    const float dy = dist/act_count_constant;

    puyo.move(x1,y1+dy,x2,y2+dy);
    ++act_count;
};