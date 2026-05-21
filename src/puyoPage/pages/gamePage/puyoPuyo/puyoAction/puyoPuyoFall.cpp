#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoPuyoFall.hpp"
#include "puyoTool/puyoCast.hpp"
#include <cmath>
#include <memory>

using namespace std;

bool puyoPuyoFall::decide(const puyoBoard& board, puyoPuyo& puyo)
{
    return true;
}
puyoPuyoFall::puyoPuyoFall(const puyoBoard& board, const puyoPuyo& puyo1, const puyoPuyo& puyo2)
    : puyoPuyoAct(0)
    , puyo1(puyo1)
    , puyo2(puyo2)
    , board(board)
{}
std::unique_ptr<puyoPuyoAct> puyoPuyoFall::clone() const
{
    auto temp = std::move(make_unique<puyoPuyoFall>(board,puyo1,puyo2));
    temp->let(act_count);
    return temp;
}

void puyoPuyoFall::act(puyoPuyo& puyo)
{
    const auto& pos1 = puyo1.get_pos();
    const auto& bsize = board.get_size();
    for(int y = pos1.y; y < bsize.y; ++y)
        if(board.touched(POSi(round(pos1.x), y+1)))
        {
            const auto pos2 = puyo2.get_pos();
            if(CASTi(round(pos2.y-pos1.y)) > 0)
                --y; // 실제로 뿌요를 배치하지 않기에 보정
            puyo.move({round(pos1.x),CASTf(y)});
            break;
        }
};