#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include "puyoPuyoVanish_temp.hpp"

using namespace std;

puyoPuyoVanish_temp::puyoPuyoVanish_temp(int amount) : puyoPuyoAct_temp(amount){};

bool puyoPuyoVanish_temp::test(puyoBoard& board, puyoPuyo& puyo)
{
    return act_count <= act_count_init;
}
bool puyoPuyoVanish_temp::decline(puyoBoard& board, puyoPuyo& puyo)
{
    if(acting() && test(board, puyo))
        return true;
    else
        halt();
    return false;
}
void puyoPuyoVanish_temp::act(puyoPuyo& puyo)
{
    ++act_count;
};

