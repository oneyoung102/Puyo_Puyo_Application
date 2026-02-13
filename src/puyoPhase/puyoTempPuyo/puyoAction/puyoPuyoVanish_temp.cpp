#include "../../puyoBoard.hpp"
#include "../puyoTempPuyo.hpp"
#include "puyoPuyoVanish_temp.hpp"

using namespace std;


puyoPuyoVanish_temp::puyoPuyoVanish_temp(int amount) : puyoPuyoAct_temp(amount){};

bool puyoPuyoVanish_temp::test_act(puyoBoard& board, puyoTempPuyo& puyo)
{
    return true;
}
bool puyoPuyoVanish_temp::decline_act(puyoBoard& board, puyoTempPuyo& puyo)
{
    if(is_acting() && test_act(board, puyo))
        return true;
    else
        halt_act();
    return false;
}
void puyoPuyoVanish_temp::act_puyo(puyoTempPuyo& puyo)
{
    if(act_count == act_count_init)
    {
        halt_act();
        return;
    }
    ++act_count;
};

bool puyoPuyoVanish_temp::vanish_soon(){return act_count*2 > act_count_init;}
