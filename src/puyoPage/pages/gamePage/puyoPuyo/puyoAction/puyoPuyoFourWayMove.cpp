#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoPuyoFourWayMove.hpp"

#include <cmath>

using namespace std;


bool puyoPuyoFourWayMove::test(puyoBoard& board, puyoPuyo& puyo)
{
    const auto[x,y] = puyo.get_pos();
    return !board.touched(ceil(y)+dy,round(x)+dx) && !board.touched(floor(y)+dy,round(x)+dx);
}

puyoPuyoFourWayMove::puyoPuyoFourWayMove(int amount, int dx, int dy)
    : puyoPuyoAct(amount)
    , dx(dx)
    , dy(dy)
{}

void puyoPuyoFourWayMove::act(puyoPuyo& puyo)
{
    const auto[x,y] = puyo.get_pos();
    const double ddx = (dx+0.0)/act_count_init, ddy = (dy+0.0)/act_count_init;
    puyo.move(x+ddx,y+ddy);
    ++act_count;
};