#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoPuyoFall.hpp"

#include <cmath>

using namespace std;

bool puyoPuyoFall::decline(puyoBoard& board, puyoPuyo& puyo)
{
    return true;
}
puyoPuyoFall::puyoPuyoFall(const puyoBoard& board, const puyoPuyo& puyo1, const puyoPuyo& puyo2)
    : puyoPuyoAct(0)
    , puyo1(puyo1)
    , puyo2(puyo2)
    , board(board)
{}

void puyoPuyoFall::act(puyoPuyo& puyo)
{
    const auto[x1,y1] = puyo1.get_pos();
    const auto [board_r, _] = board.get_size();
    for(int y = y1; y < board_r; ++y)
        if(board.touched(y+1,round(x1)))
        {
            const auto[_,y2] = puyo2.get_pos();
            if(round(y1) < round(y2))
                --y; // 실제로 뿌요를 배치하지 않기에 보정
            puyo.move(round(x1),y);
            break;
        }
};