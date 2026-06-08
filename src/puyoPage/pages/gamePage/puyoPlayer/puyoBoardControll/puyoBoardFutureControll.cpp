#include "puyoPage/pages/gamePage/puyoPlayer/puyoBoardControll/puyoBoardFutureControll.hpp"
#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoAction/puyoPuyoFall.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include <memory>

using namespace std;

puyoBoardFutureControll::puyoBoardFutureControll(){}

const vector<puyoPuyo> &puyoBoardFutureControll::get() const { return future_puyos; }

void puyoBoardFutureControll::spawn(const puyoBoard& board, const puyoPlayPuyo& play_puyo)
{
    future_puyos.clear();
    for(size_t i = 0 ; i < 2 ; ++i)
    {
        auto temp_puyo = play_puyo.get_each(i);
        temp_puyo.set_act(make_unique<puyoPuyoFall>(board,play_puyo.get_each(i),play_puyo.get_each(i^1)));
        future_puyos.push_back(std::move(temp_puyo));
    }
}

void puyoBoardFutureControll::fall(const puyoBoard& board)
{
    for(auto& future_puyo : future_puyos)
        future_puyo.act_let(board);
}
