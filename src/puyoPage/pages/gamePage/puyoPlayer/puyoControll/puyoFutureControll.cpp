#include "puyoPage/pages/gamePage/puyoPlayer/puyoControll/puyoFutureControll.hpp"
#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoAction/puyoPuyoFall.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include <memory>

using namespace std;

puyoFutureControll::puyoFutureControll(){}

const vector<puyoPuyo> &puyoFutureControll::view() const { return future_puyos; }

void puyoFutureControll::spawn(const puyoBoard& board, const puyoPlayPuyo& play_puyo)
{
    future_puyos.clear();
    for(size_t i = 0 ; i < 2 ; ++i)
    {
        auto temp_puyo = play_puyo.view_each(i);
        temp_puyo.set_act(make_unique<puyoPuyoFall>(board,play_puyo.view_each(i),play_puyo.view_each(i^1)));
        future_puyos.push_back(std::move(temp_puyo));
    }
}

void puyoFutureControll::fall(const puyoBoard& board)
{
    for(auto& future_puyo : future_puyos)
        future_puyo.act_let(board);
}
