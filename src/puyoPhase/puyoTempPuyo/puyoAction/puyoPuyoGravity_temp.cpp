#include "../../puyoBoard.hpp"
#include "../puyoTempPuyo.hpp"
#include "puyoPuyoGravity_temp.hpp"

using namespace std;


puyoPuyoGravity_temp::puyoPuyoGravity_temp(int amount) : puyoPuyoAct_temp(amount){};

bool puyoPuyoGravity_temp::test_act(puyoBoard& board, puyoTempPuyo& puyo)
{
    const auto[x,y] = puyo.get_puyo_pos();
    return !puyo.puyo_touched(board,round(x),y+1);
}
bool puyoPuyoGravity_temp::decline_act(puyoBoard& board, puyoTempPuyo& puyo)
{
    if(is_acting() && test_act(board, puyo))
        return true;
    else
        halt_act();
    return false;
}
void puyoPuyoGravity_temp::act_puyo(puyoTempPuyo& puyo)
{
    const auto[x,y] = puyo.get_puyo_pos();
    const float dy = 1.0/act_count_init;
    puyo.move_puyo(x,y+dy);
    ++act_count;
};
