#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include "puyoPuyoFly.hpp"

using namespace std;


puyoPuyoFly::puyoPuyoFly(POSf from_pos, POSf to_pos, int amount)
    //다른 act는 좌표가 보드 기준인데 반해, fly는 전체 스크린 기준 좌표
    : puyoPuyoAct(amount)
    , from_pos(from_pos)
    , dpos(to_pos-from_pos) 
{}

void puyoPuyoFly::arrive(puyoPuyo& puyo){}

void puyoPuyoFly::act(puyoPuyo& puyo)
{
    const float progress = (float)act_count/act_count_init;
    puyo.move(from_pos+POSf(dpos.x*progress,dpos.y*progress*progress));//제곱 맞음
    ++act_count;
};