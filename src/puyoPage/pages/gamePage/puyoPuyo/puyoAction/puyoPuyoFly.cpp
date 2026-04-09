#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include "puyoPuyoFly.hpp"

using namespace std;


puyoPuyoFly::puyoPuyoFly(double fx, double fy, double tx, double ty, int amount)
    //다른 act는 좌표가 보드 기준인데 반해, fly는 전체 스크린 기준 좌표
    : puyoPuyoAct(amount)
    , from_x(fx) 
    , from_y(fy)
    , to_x(tx)
    , to_y(ty)
{}

void puyoPuyoFly::arrive(puyoPuyo& puyo){}

void puyoPuyoFly::act(puyoPuyo& puyo)
{
    const double progress = (double)act_count/act_count_init;
    const int dx = to_x-from_x, dy = to_y-from_y;
    const int nx = from_x+dx*progress, ny = from_y + dy*progress*progress;//제곱 맞음
    puyo.move(nx,ny);
    ++act_count;
};