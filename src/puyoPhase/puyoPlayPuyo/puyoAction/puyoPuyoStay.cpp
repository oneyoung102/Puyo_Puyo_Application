#include "../../puyoBoard.hpp"
#include "../puyoPlayPuyo.hpp"
#include "puyoPuyoStay.hpp"

using namespace std;

puyoPuyoStay::puyoPuyoStay(int amount, int b) : puyoPuyoAct(amount)
{
    act_count = 0;
    bonus_count = b;
    destroy = false;
}

bool puyoPuyoStay::test_act(puyoBoard& board, puyoPlayPuyo& puyo)
{
    return puyo.is_holding();
}
bool puyoPuyoStay::decline_act(puyoBoard& board, puyoPlayPuyo& puyo)
{
    if(test_act(board,puyo))
        return true;
    return false;
}
void puyoPuyoStay::act_puyo(puyoPlayPuyo& puyo)
{
    if(act_count == act_count_constant)
    {
        destroy = true;
        halt_act();
    }
    ++act_count;
};
void puyoPuyoStay::more_stay()
{
    act_count = max(act_count-bonus_count,0);
    bonus_count /= 2;
}
bool puyoPuyoStay::is_destroyed(){return destroy;}

