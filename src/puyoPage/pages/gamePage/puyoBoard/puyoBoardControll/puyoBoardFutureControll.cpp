#include "puyoPage/pages/gamePage/puyoBoard/puyoBoardControll/puyoBoardFutureControll.hpp"
#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"

using namespace std;

puyoBoardFutureControll::puyoBoardFutureControll(){};

vector<puyoPuyo> &puyoBoardFutureControll::get() { return future_puyos; }

void puyoBoardFutureControll::find(puyoBoard& board, puyoPlayPuyo &puyo)
{
    future_puyos.clear();
    const auto [x1, y1, x2, y2] = puyo.get_pos();
    const auto [color1, color2] = puyo.get_types();
    const auto [board_r, board_c] = board.get_size();
    for(int y = (int)y1; y < board_r; ++y)
        if(puyo.touched(board, round(x1), y + 1))
        {
            if (y1 < y2)
                --y; // 실제로 뿌요를 배치하지 않기에 보정
            future_puyos.push_back(puyoPuyo(round(x1), y, color1));
            break;
        }
    for(int y = (int)y2; y < board_r; ++y)
        if(puyo.touched(board, round(x2), y + 1))
        {
            if (y1 > y2)
                --y; // 실제로 뿌요를 배치하지 않기에 보정
            future_puyos.push_back(puyoPuyo(round(x2), y, color2));
            break;
        }
}
void puyoBoardFutureControll::kill() { future_puyos.clear(); }
