#include "puyoBoard.hpp"

#include "puyoPuyo/puyoPuyoAct.hpp"
#include "puyoPuyo/puyoPuyoLeft.hpp"
#include "puyoPuyo/puyoPuyoRight.hpp"
#include "puyoPuyo/puyoPuyoDown.hpp"
#include "puyoPuyo/puyoPuyoUp.hpp"
#include "puyoPuyo/puyoPuyoTurn.hpp"
#include "puyoPuyo/puyoPuyoDrop.hpp"
#include "puyoPuyo/puyoPuyoFall.hpp"
#include "puyoPuyo.hpp"

#include <tuple>
#include <utility>
#include <cmath>
#include <functional>


using namespace std;


puyoPuyo::puyoPuyo(float spawn_x1, float spawn_y1, int c1, int c2)
{
    left  = new puyoPuyoLeft(400,1);
    right = new puyoPuyoRight(400,1);
    up    = new puyoPuyoUp(400,1);
    down  = new puyoPuyoDown(400,1);
    turn  = new puyoPuyoTurn(400,90);
    drop  = new puyoPuyoDrop(450);
    fall  = new puyoPuyoFall(2300,1);
    action = nullptr;

    acts.push_back(turn);
    acts.push_back(left);
    acts.push_back(right);
    acts.push_back(up);
    acts.push_back(down);
    acts.push_back(drop);

    tie(x1,y1) = make_pair(spawn_x1,spawn_y1-1);
    tie(x2,y2) = make_pair(spawn_x1,spawn_y1-2);
    color1 = c1;
    color2 = c2;
}

void puyoPuyo::act_let(puyoBoard& board)
{
    if(action == nullptr)
    {
        for(auto act : acts)//행동 찾기
            if(act->is_acting() && act->decline_act(board,*this))
            {
                action = act;
                return;
            }
    }
    else
    {
        for(auto act : acts)//현재 행동 중에 들어오는 행동 무시
            if(action != act && act->is_acting())
                act->halt_act();
        if(action->is_acting())
            action->act_puyo(*this);
        else
            action = nullptr;
    }
}

void puyoPuyo::act_fall(puyoBoard& board)
{
    if((turn->is_acting() && !fall->is_acting()) || up->is_acting() || drop->is_acting())
        return;
    if(fall->decline_act(board,*this))
        fall->act_puyo(*this);
}

void puyoPuyo::deploy_puyo(puyoBoard& board)
{
    board.insert_puyo(round(y1),round(x1),color1);
    board.insert_puyo(round(y2),round(x2),color2);
}

bool puyoPuyo::puyo_touched(puyoBoard& board, int ix, int iy)
{
    return iy >= 0 && (!board.is_in_board(iy,ix) || board.get_puyo(iy,ix) != -1)
        || iy < 0 && !board.is_in_col(ix);
}

tuple<float,float,float,float> puyoPuyo::get_puyo_pos(){return make_tuple(x1,y1,x2,y2);}
void puyoPuyo::move_puyo(float to_x1, float to_y1, float to_x2, float to_y2)
{
    x1 = to_x1;
    y1 = to_y1;
    x2 = to_x2;
    y2 = to_y2;
}
pair<int,int> puyoPuyo::get_puyo_color(){return make_pair(color1,color2);}

function<void()> puyoPuyo::get_let_left(){return [this](){return left->let_act();};}
function<void()> puyoPuyo::get_let_right(){return [this](){return right->let_act();};}
function<void()> puyoPuyo::get_let_down(){return [this](){return down->let_act();};}
//function<void()> puyoPuyo::get_let_up(){return [this](){return up->let_act();};}
function<void()> puyoPuyo::get_let_turn(){return [this](){return turn->let_act();};}
function<void()> puyoPuyo::get_let_drop(){return [this](){return drop->let_act();};}