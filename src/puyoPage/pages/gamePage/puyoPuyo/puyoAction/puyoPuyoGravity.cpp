#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include "puyoPuyoGravity.hpp"

using namespace std;


puyoPuyoGravity::puyoPuyoGravity(int amount, int stay_value)
    : puyoPuyoAct(amount)
    , stay_value(stay_value)
{
    stay = 0;
}

bool puyoPuyoGravity::test(puyoBoard& board, puyoPuyo& puyo)
{
    const auto[x,y] = puyo.get_pos();
    return !board.touched(floor(y)+1,round(x));
}
void puyoPuyoGravity::arrive(puyoPuyo& puyo)
{
    const auto[x,y] = puyo.get_pos();
    puyo.move(round(x),floor(y));
}
bool puyoPuyoGravity::decline(puyoBoard& board, puyoPuyo& puyo)
{
    if(test(board, puyo))
    {
        stay = 0;
        return true;
    }
    else if(stay < stay_value)
    {
        if(stay == 0)
            arrive(puyo);
        ++stay;
    }
    else
        halt();
    return false;
}
void puyoPuyoGravity::act(puyoPuyo& puyo)
{
    const auto[x,y] = puyo.get_pos();
    const double dy = 1.0/act_count_init;
    puyo.move(x,y+dy);
    if(act_count >= act_count_init-1)
        act_count = 0;
    else 
        ++act_count;
};

