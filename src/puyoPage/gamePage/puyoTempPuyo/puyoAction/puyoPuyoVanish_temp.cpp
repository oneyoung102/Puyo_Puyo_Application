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

bool puyoPuyoVanish_temp::vanish_soon(){return act_count < act_count_init*0.85;}
bool puyoPuyoVanish_temp::vanish_stay(){return act_count < act_count_init*0.7;}
