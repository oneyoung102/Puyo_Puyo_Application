#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include "puyoPuyoFly_temp.hpp"

using namespace std;


puyoPuyoFly_temp::puyoPuyoFly_temp(float fx, float fy, float tx, float ty, int amount) : puyoPuyoAct_temp(amount)
{
    from_x = fx;
    from_y = fy;
    to_x = tx;
    to_y = ty;
};

bool puyoPuyoFly_temp::test(puyoBoard& board, puyoPuyo& puyo)
{
    return act_count <= act_count_init;
}
bool puyoPuyoFly_temp::decline(puyoBoard& board, puyoPuyo& puyo)
{
    if(acting() && test(board, puyo))
        return true;
    else
        halt();
    return false;
}
void puyoPuyoFly_temp::act(puyoPuyo& puyo)
{
    const auto[x,y] = puyo.get_pos();
    const float progress = (float)act_count/act_count_init;
    const int dx = to_x-from_x, dy = to_y-from_y;
    const int nx = from_x+dx*progress, ny = from_y + dy*progress*progress;//제곱 맞음
    puyo.move(nx,ny);
    ++act_count;
};