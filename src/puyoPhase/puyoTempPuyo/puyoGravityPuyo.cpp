#include "../puyoBoard.hpp"

#include "puyoAction/puyoPuyoGravity_temp.hpp"
#include "puyoGravityPuyo.hpp"
#include "puyoTempPuyo.hpp"

#include <memory>


using namespace std;

puyoGravityPuyo::puyoGravityPuyo(float xx, float yy, int c, int amount) : puyoTempPuyo(xx,yy,c)
{  
    gravity = make_unique<puyoPuyoGravity_temp>(amount);
    gravity->let_act();
}
void puyoGravityPuyo::gravity_let(puyoBoard& board) // 
{
    if(gravity->decline_act(board,*this))
        gravity->act_puyo(*this);
}

bool puyoGravityPuyo::gravity_stopped(){return !gravity->is_acting();}