#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoTempPuyo/puyoTempPuyo.hpp"
#include "puyoPuyoFly_temp.hpp"

using namespace std;


puyoPuyoFly_temp::puyoPuyoFly_temp(float fx, float fy, float tx, float ty,int amount) : puyoPuyoAct_temp(amount)
{
    from_x = fx;
    from_y = fy;
    to_x = tx;
    to_y = ty;
};

bool puyoPuyoFly_temp::test_act(puyoBoard& board, puyoTempPuyo& puyo)
{
    return act_count <= act_count_init;
}
bool puyoPuyoFly_temp::decline_act(puyoBoard& board, puyoTempPuyo& puyo)
{
    if(is_acting() && test_act(board, puyo))
        return true;
    else
        halt_act();
    return false;
}
void puyoPuyoFly_temp::act_puyo(puyoTempPuyo& puyo)
{
    const auto[x,y] = puyo.get_puyo_pos();
    const float progress = (float)act_count/act_count_init;
    const int dx = to_x-from_x, dy = to_y-from_y;
    const int nx = from_x+dx*progress, ny = from_y + dy*progress*progress;//제곱 맞음
    puyo.move_puyo(nx,ny);
    ++act_count;
};