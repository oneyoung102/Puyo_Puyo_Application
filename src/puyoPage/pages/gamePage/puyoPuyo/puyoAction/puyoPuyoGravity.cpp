#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include <memory>
#include "puyoPuyoGravity.hpp"

using namespace std;


puyoPuyoGravity::puyoPuyoGravity(int amount)
    : puyoPuyoAct(amount)
{}
std::unique_ptr<puyoPuyoAct> puyoPuyoGravity::clone() const
{
    auto temp = make_unique<puyoPuyoGravity>(act_count_init);
    temp->let(act_count);
    return temp;
}

bool puyoPuyoGravity::test(const puyoBoard& board, puyoPuyo& puyo)
{
    const auto[x,y] = puyo.get_pos();
    return !board.touched(POSi(round(x), floor(y)+1));
}
void puyoPuyoGravity::arrive(puyoPuyo& puyo)
{
    const auto[x,y] = puyo.get_pos();
    puyo.move({round(x),floor(y)});
}
bool puyoPuyoGravity::decide(const puyoBoard& board, puyoPuyo& puyo)
{
    if(test(board, puyo))
        return true;
    halt();
    arrive(puyo);
    return false;
}
void puyoPuyoGravity::act(puyoPuyo& puyo)
{
    const float dy = 1.0/act_count_init;
    puyo.move(puyo.get_pos()+POSf(0,dy));
};

