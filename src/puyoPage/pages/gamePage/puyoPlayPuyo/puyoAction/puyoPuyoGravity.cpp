#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoPuyoGravity.hpp"

using namespace std;

puyoPuyoGravity::puyoPuyoGravity(int amount, float dist): puyoPuyoAct(amount)
{
    this->dist = dist;
    act_count = 0;
}
bool puyoPuyoGravity::test_act(puyoBoard& board, puyoPlayPuyo& puyo)
{
    const auto[x1,y1,x2,y2] = puyo.get_puyo_pos();
    return !puyo.puyo_touched(board,x1,y1+1) && !puyo.puyo_touched(board,x2,y2+1);
}
bool puyoPuyoGravity::decline_act(puyoBoard& board, puyoPlayPuyo& puyo)
{
    const auto[x1,y1,x2,y2] = puyo.get_puyo_pos();
    if(test_act(board, puyo))
    {
        if(!is_acting())
            let_act();
        return true;
    }
    else
    {
        halt_act();
        return false;
    }
    return false;
}
void puyoPuyoGravity::act_puyo(puyoPlayPuyo& puyo)
{
    if(act_count == act_count_constant)
        act_count = 0;
    const auto[x1,y1,x2,y2] = puyo.get_puyo_pos();
    const float dy = dist/act_count_constant;

    puyo.move_puyo(x1,y1+dy,x2,y2+dy);
    ++act_count;
};