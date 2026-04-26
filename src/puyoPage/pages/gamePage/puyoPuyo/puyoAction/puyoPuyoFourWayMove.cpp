#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoPuyoFourWayMove.hpp"

#include <cmath>

using namespace std;


bool puyoPuyoFourWayMove::test(const puyoBoard& board, puyoPuyo& puyo)
{
    const auto[x,y] = puyo.get_pos();
    return !board.touched(ceil(y)+dpos.y,round(x)+dpos.x) && !board.touched(floor(y)+dpos.y,round(x)+dpos.x);
}

puyoPuyoFourWayMove::puyoPuyoFourWayMove(int amount, POS delta)
    : puyoPuyoAct(amount)
    , dpos(delta)
{}

void puyoPuyoFourWayMove::act(puyoPuyo& puyo)
{
    puyo.move(dpos/act_count_init+puyo.get_pos());
    ++act_count;
};