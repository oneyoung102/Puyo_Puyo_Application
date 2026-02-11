#include "../puyoBoard.hpp"
#include "../puyoPhase/puyoTempPuyo.hpp"
#include "puyoPuyoGravity.hpp"

using namespace std;


puyoPuyoGravity::puyoPuyoGravity(int amount)
{
    gravity_count_init = amount;
    gravity_count = 0;
}

bool puyoPuyoGravity::test_gravity(puyoBoard& board, puyoTempPuyo& puyo)
{
    const auto[x,y] = puyo.get_puyo_pos();
    return !puyo.puyo_touched(board,x,y+1);
}
bool puyoPuyoGravity::decline_gravity(puyoBoard& board, puyoTempPuyo& puyo)
{
    if(test_gravity(board, puyo))
        return true;
    else
    {
        halt_gravity();
        return false;
    }
    return false;
}
void puyoPuyoGravity::gravity_puyo(puyoTempPuyo& puyo)
{
    if(gravity_count == gravity_count_init)
        gravity_count = 0;
    const auto[x,y] = puyo.get_puyo_pos();
    const float dy = 1.0/gravity_count_init;
    puyo.move_puyo(x,y+dy);
    ++gravity_count;
};
bool puyoPuyoGravity::is_gravity_ing(){return gravity_count != -1;}
void puyoPuyoGravity::let_gravity(){if(!is_gravity_ing()) gravity_count = 0;}
void puyoPuyoGravity::halt_gravity(){gravity_count = -1;}
