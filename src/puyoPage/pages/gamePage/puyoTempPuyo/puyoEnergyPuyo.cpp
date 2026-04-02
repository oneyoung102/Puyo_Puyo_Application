#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"

#include "puyoAction/puyoPuyoFly_temp.hpp"
#include "puyoEnergyPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoTempPuyo/puyoTempPuyo.hpp"

#include <memory>


using namespace std;

puyoEnergyPuyo::puyoEnergyPuyo(float fx, float fy, float tx, float ty, puyoType type, int amount) : puyoTempPuyo(fx,fy,type)
{  
    fly = make_unique<puyoPuyoFly_temp>(fx,fy,tx,ty,amount);
    fly->let_act();
}
void puyoEnergyPuyo::fly_let(puyoBoard& board)
{
    if(fly->decline_act(board,*this))
        fly->act_puyo(*this);
}

bool puyoEnergyPuyo::fly_stopped(){return !fly->is_acting();}
