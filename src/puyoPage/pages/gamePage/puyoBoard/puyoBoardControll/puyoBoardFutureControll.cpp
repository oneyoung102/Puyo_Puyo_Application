#include "puyoPage/pages/gamePage/puyoBoard/puyoBoardControll/puyoBoardFutureControll.hpp"
#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoAction/puyoPuyoFall.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include <memory>

using namespace std;

puyoBoardFutureControll::puyoBoardFutureControll(){}

const vector<puyoPuyo> &puyoBoardFutureControll::get() { return future_puyos; }

void puyoBoardFutureControll::update(const puyoBoard& board, puyoPlayPuyo& puyo)
{
    future_puyos.clear();
    for(size_t i = 0 ; i < 2 ; ++i)
    {
        const auto& one_puyo = puyo.get_each(i);
        future_puyos.push_back(puyoPuyo(one_puyo->get_pos(),one_puyo->get_type(),
            std::move(make_unique<puyoPuyoFall>(board,*one_puyo,*puyo.get_each(i^1)))));
    }
}

void puyoBoardFutureControll::fall(const puyoBoard& board)
{
    for(auto& future_puyo : future_puyos)
        future_puyo.act_let(board);
}
