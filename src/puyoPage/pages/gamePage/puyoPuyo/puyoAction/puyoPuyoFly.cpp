#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include "puyoPuyoFly.hpp"

using namespace std;


puyoPuyoFly::puyoPuyoFly(pair<float,float> from_pos, pair<float,float> to_pos, int amount)
    //다른 act는 좌표가 보드 기준인데 반해, fly는 전체 스크린 기준 좌표
    : puyoPuyoAct(amount)
    , from_x(from_pos.first) 
    , from_y(from_pos.second)
    , to_x(to_pos.first)
    , to_y(to_pos.second)
{}

void puyoPuyoFly::arrive(puyoPuyo& puyo){}

void puyoPuyoFly::act(puyoPuyo& puyo)
{
    const float progress = (float)act_count/act_count_init;
    const int dx = to_x-from_x, dy = to_y-from_y;
    const int nx = from_x+dx*progress, ny = from_y + dy*progress*progress;//제곱 맞음
    puyo.move(nx,ny);
    ++act_count;
};