#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"

#include "puyoAction/puyoPuyoGravity_temp.hpp"
#include "puyoGravityPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoTempPuyo/puyoTempPuyo.hpp"

#include <memory>


using namespace std;

puyoGravityPuyo::puyoGravityPuyo(float xx, float yy, puyoType c, int amount) : puyoTempPuyo(xx,yy,c)
{  
    gravity = make_unique<puyoPuyoGravity_temp>(amount);
    gravity->let_act();
}
void puyoGravityPuyo::gravity_let(puyoBoard& board) // 
{
    if(gravity->decline_act(board,*this))
        gravity->act_puyo(*this);
}

bool puyoGravityPuyo::deploy_puyo(puyoBoard& board)
{
    const int ix = round(x), iy = round(y);
    if(!board.is_in_board(iy,ix))
        return false; 
    board.insert_puyo(color,iy,ix);
    return true;
}

bool puyoGravityPuyo::gravity_stopped(){return !gravity->is_acting();}
bool puyoGravityPuyo::is_fast(){return gravity->is_fast();}
