#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoPuyoStay.hpp"

using namespace std;

puyoPuyoStay::puyoPuyoStay(int amount, int bonus_count) : puyoPuyoAct(amount)
{
    act_count = 0;
    this->bonus_count = bonus_count;//뿌요가 닿은 상태로 움직이면 추가로 주는 시간
    destroy = false;
}

bool puyoPuyoStay::test(puyoBoard& board, puyoPlayPuyo& puyo)
{
    return puyo.holding();
}
bool puyoPuyoStay::decline(puyoBoard& board, puyoPlayPuyo& puyo)
{
    if(test(board,puyo))
        return true;
    return false;
}
void puyoPuyoStay::act(puyoPlayPuyo& puyo)
{
    if(act_count == act_count_constant)
    {
        destroy = true;
        halt();
    }
    ++act_count;
};
void puyoPuyoStay::more_stay()
{
    act_count = max(act_count-bonus_count,0);
    bonus_count /= 2;
}
bool puyoPuyoStay::broken(){return destroy;}

