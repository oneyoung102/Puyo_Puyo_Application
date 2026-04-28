#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoPuyoFourWayMove.hpp"

#include <cmath>

using namespace std;


bool puyoPuyoFourWayMove::test(const puyoBoard& board, puyoPuyo& puyo)
{
    const auto[x,y] = puyo.get_pos();
    return !board.touched(POSi(round(x), ceil(y))+dpos) && !board.touched(POSi(round(x), floor(y))+dpos);
}

puyoPuyoFourWayMove::puyoPuyoFourWayMove(int amount, POSf dpos)
    : puyoPuyoAct(amount)
    , dpos(dpos)
{}

void puyoPuyoFourWayMove::act(puyoPuyo& puyo)
{
    puyo.move(dpos/act_count_init+puyo.get_pos());
    ++act_count;
};