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

puyoPuyoFourWayMove::puyoPuyoFourWayMove(int amount, std::pair<float,float> delta)
    : puyoPuyoAct(amount)
    , dx(delta.first)
    , dy(delta.second)
{}

void puyoPuyoFourWayMove::act(puyoPuyo& puyo)
{
    const auto[x,y] = puyo.get_pos();
    const float ddx = (dx+0.0)/act_count_init, ddy = (dy+0.0)/act_count_init;
    puyo.move(x+ddx,y+ddy);
    ++act_count;
};