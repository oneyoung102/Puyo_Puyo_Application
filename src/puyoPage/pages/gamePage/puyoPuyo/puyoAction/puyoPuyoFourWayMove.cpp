#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoPuyoFourWayMove.hpp"

#include <cmath>
#include <memory>

using namespace std;


bool puyoPuyoFourWayMove::test(const puyoBoard& board, puyoPuyo& puyo)
{
    const auto[x,y] = puyo.get_pos();
    constexpr float EPSILON = 0.01f;
    return !board.touched(POSi(round(x), floor(y + EPSILON))+dpos) && !board.touched(POSi(round(x), ceil(y - EPSILON))+dpos);
}

puyoPuyoFourWayMove::puyoPuyoFourWayMove(int amount, POSf dpos)
    : puyoPuyoAct(amount)
    , dpos(dpos)
{}
std::unique_ptr<puyoPuyoAct> puyoPuyoFourWayMove::clone() const
{
    auto temp = make_unique<puyoPuyoFourWayMove>(act_count_init,dpos);
    temp->let(act_count);
    return temp;
}

void puyoPuyoFourWayMove::act(puyoPuyo& puyo)
{
    puyo.move(dpos/act_count_init+puyo.get_pos());
    ++act_count;
};