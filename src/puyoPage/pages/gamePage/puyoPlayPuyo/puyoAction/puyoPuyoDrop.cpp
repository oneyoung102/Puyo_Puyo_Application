#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoPuyoDrop.hpp"

using namespace std;

bool puyoPuyoDrop::test_act(puyoBoard& board,puyoPlayPuyo& puyo){return true;}
bool puyoPuyoDrop::decline_act(puyoBoard& board,puyoPlayPuyo& puyo){return true;}

puyoPuyoDrop::puyoPuyoDrop(int amount) : puyoPuyoAct(amount){}

void puyoPuyoDrop::act_puyo(puyoPlayPuyo& puyo)
{
    act_count = 0;
};
