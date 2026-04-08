#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include "puyoPuyoGravity_temp.hpp"

using namespace std;


puyoPuyoGravity_temp::puyoPuyoGravity_temp(int amount) : puyoPuyoAct_temp(amount){};

bool puyoPuyoGravity_temp::test(puyoBoard& board, puyoPuyo& puyo)
{
    const auto[x,y] = puyo.get_pos();
    return !puyo.touched(board,round(x),y+1);
}
bool puyoPuyoGravity_temp::decline(puyoBoard& board, puyoPuyo& puyo)
{
    if(acting() && test(board, puyo))
        return true;
    else
        halt();
    return false;
}
void puyoPuyoGravity_temp::act(puyoPuyo& puyo)
{
    const auto[x,y] = puyo.get_pos();
    const float dy = 1.0/act_count_init;
    puyo.move(x,y+dy);
    ++act_count;
};

