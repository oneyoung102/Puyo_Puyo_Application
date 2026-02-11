#include "../puyoBoard.hpp"
#include "../puyoPlayPuyo.hpp"
#include "puyoPuyoFall.hpp"

using namespace std;

puyoPuyoFall::puyoPuyoFall(int amount, float d): puyoPuyoAct(amount)
{
    dist = d;
    act_count = 0;
}

void puyoPuyoFall::arrive(puyoPlayPuyo& puyo, float x1,float y1,float x2,float y2)
{
    puyo.move_puyo(round(x1),round(y1),
                    round(x2),round(y2));
}

bool puyoPuyoFall::test_act(puyoBoard& board, puyoPlayPuyo& puyo)
{
    const auto[x1,y1,x2,y2] = puyo.get_puyo_pos();
    return !puyo.puyo_touched(board,x1,y1+1) && !puyo.puyo_touched(board,x2,y2+1);
}
bool puyoPuyoFall::decline_act(puyoBoard& board, puyoPlayPuyo& puyo)
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
        if(is_acting())
        {
            arrive(puyo,x1,y1,x2,y2);
            halt_act();
        }
        return false;
    }
    return false;
}
void puyoPuyoFall::act_puyo(puyoPlayPuyo& puyo)
{
    if(act_count == act_count_constant)
        act_count = 0;
    const auto[x1,y1,x2,y2] = puyo.get_puyo_pos();
    const float dy = dist/act_count_constant;

    puyo.move_puyo(x1,y1+dy,x2,y2+dy);
    ++act_count;
};