#include "../puyoBoard.hpp"

#include "puyoAction/puyoPuyoVanish_temp.hpp"
#include "puyoVanishPuyo.hpp"
#include "puyoTempPuyo.hpp"

#include <memory>


using namespace std;

puyoVanishPuyo::puyoVanishPuyo(float xx, float yy, int c, int amount) : puyoTempPuyo(xx,yy,c)
{
    vanish = make_unique<puyoPuyoVanish_temp>(amount);
    vanish->let_act();
}

bool puyoVanishPuyo::vanish_stopped(){return !vanish->is_acting();}


void puyoVanishPuyo::vanish_let(puyoBoard& board) // 
{
    if(vanish->decline_act(board,*this))
        vanish->act_puyo(*this);
}
bool puyoVanishPuyo::vanish_soon(){return vanish->vanish_soon();}