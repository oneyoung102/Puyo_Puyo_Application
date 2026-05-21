#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include "puyoTool/puyoCast.hpp"
#include "puyoPuyoFly.hpp"

using namespace std;


puyoPuyoFly::puyoPuyoFly(int amount, const POSf& from_pos, const POSf& dpos)
    //다른 act는 좌표가 보드 기준인데 반해, fly는 전체 스크린 기준 좌표
    : puyoPuyoAct(amount)
    , from_pos(from_pos)
    , dpos(dpos) 
{}
std::unique_ptr<puyoPuyoAct> puyoPuyoFly::clone() const
{
    auto temp = make_unique<puyoPuyoFly>(act_count_init,from_pos,dpos);
    temp->let(act_count);
    return temp;
}

void puyoPuyoFly::arrive(puyoPuyo& puyo){}

void puyoPuyoFly::act(puyoPuyo& puyo)
{
    const float progress = CASTf(act_count)/act_count_init;
    puyo.move(from_pos+dpos*POSf(progress,progress*progress));//제곱 맞음
    ++act_count;
};