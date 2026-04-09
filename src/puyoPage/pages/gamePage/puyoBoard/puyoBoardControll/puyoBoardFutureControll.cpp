#include "puyoPage/pages/gamePage/puyoBoard/puyoBoardControll/puyoBoardFutureControll.hpp"
#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoAction/puyoPuyoFall.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include <memory>

using namespace std;

puyoBoardFutureControll::puyoBoardFutureControll(){}

const vector<puyoPuyo> &puyoBoardFutureControll::get() { return future_puyos; }

void puyoBoardFutureControll::set(puyoBoard& board, puyoPlayPuyo& puyo)
{
    future_puyos.clear();
    for(int i = 0 ; i < 2 ; ++i)
    {
        const auto[x,y] = puyo.get_each(i)->get_pos();
        const auto type = puyo.get_each(i)->get_type();
        future_puyos.push_back(puyoPuyo(x,y,type,
            std::move(make_unique<puyoPuyoFall>(board,*puyo.get_each(i),*puyo.get_each(i^1)))));
    }
}

void puyoBoardFutureControll::fall(puyoBoard& board)
{
    for(auto& future_puyo : future_puyos)
        future_puyo.act_let(board);
}
