#include "puyoBoard.hpp"

#include "puyoAction/puyoPuyoAct.hpp"
#include "puyoAction/puyoPuyoLeft.hpp"
#include "puyoAction/puyoPuyoRight.hpp"
#include "puyoAction/puyoPuyoDown.hpp"
#include "puyoAction/puyoPuyoUp.hpp"
#include "puyoAction/puyoPuyoTurn.hpp"
#include "puyoAction/puyoPuyoDrop.hpp"
#include "puyoAction/puyoPuyoFall.hpp"
#include "puyoAction/puyoPuyoStay.hpp"
#include "puyoPlayPuyo.hpp"
#include "puyoPhase/puyoTempPuyo.hpp"

#include <tuple>
#include <utility>
#include <cmath>
#include <functional>


using namespace std;


puyoPlayPuyo::puyoPlayPuyo(pair<float,float> spawn_pos, pair<int,int> color)
{
    left  = new puyoPuyoLeft(400,1);
    right = new puyoPuyoRight(400,1);
    up    = new puyoPuyoUp(400,1);
    down  = new puyoPuyoDown(400,1);
    turn  = new puyoPuyoTurn(360,90);
    drop  = new puyoPuyoDrop(-1);
    fall  = new puyoPuyoFall(1800,1);
    action = nullptr;
    stay  = new puyoPuyoStay(2000,200);

    acts.push_back(turn);
    acts.push_back(left);
    acts.push_back(right);
    acts.push_back(up);
    acts.push_back(down);

    tie(x1,y1) = spawn_pos;
    tie(x2,y2) = make_pair(spawn_pos.first,spawn_pos.second-1);
    tie(color1,color2) = color;
}

bool puyoPlayPuyo::act_let(puyoBoard& board)
{
    if(drop->is_acting())
        return false;
    if(action == nullptr)
    {
        for(auto act : acts)//행동 찾기
            if(act->is_acting() && act->decline_act(board,*this))
            {
                action = act;
                break;
            }
    }
    else
    {
        /*for(auto act : acts)//현재 행동 중에 들어오는 행동 무시
            if(action != act && act->is_acting())
                act->halt_act();*/
        if(action->is_acting())
            action->act_puyo(*this);
        else
            action = nullptr;
    }
    return true;
}

bool puyoPlayPuyo::act_fall(puyoBoard& board)
{
    //if(action == nullptr)
    {
        if(fall->decline_act(board,*this))
            fall->act_puyo(*this);
    }
    if(stay->decline_act(board,*this))
    {
        stay->act_puyo(*this);
        if(action != nullptr)
            stay->more_stay();
        if(stay->is_destroyed())
            return false;
    }
    return true;
}

bool puyoPlayPuyo::is_holding(){return !fall->is_acting();}

vector<puyoTempPuyo> puyoPlayPuyo::to_temp_puyo()
{
    if(y1 < y2)//y좌표가 큰 게 먼저 오게
    {
        swap(x1,x2);
        swap(y1,y2);
        swap(color1,color2);
    }
    return {puyoTempPuyo(x1,y1,color1),puyoTempPuyo(x2,y2,color2)};
}

bool puyoPlayPuyo::puyo_touched(puyoBoard& board, int ix, int iy)
{
    return iy >= 0 && (!board.is_in_board(iy,ix) || board.get_puyo(iy,ix) != -1)
        || iy < 0 && !board.is_in_col(ix);
}

tuple<float,float,float,float> puyoPlayPuyo::get_puyo_pos(){return make_tuple(x1,y1,x2,y2);}
void puyoPlayPuyo::move_puyo(float to_x1, float to_y1, float to_x2, float to_y2)
{
    x1 = to_x1;
    y1 = to_y1;
    x2 = to_x2;
    y2 = to_y2;
}
pair<int,int> puyoPlayPuyo::get_puyo_color(){return make_pair(color1,color2);}

function<void()> puyoPlayPuyo::get_let_left(){return [this](){return left->let_act();};}
function<void()> puyoPlayPuyo::get_let_right(){return [this](){return right->let_act();};}
function<void()> puyoPlayPuyo::get_let_down(){return [this](){return down->let_act();};}
//function<void()> puyoPlayPuyo::get_let_up(){return [this](){return up->let_act();};}
function<void()> puyoPlayPuyo::get_let_turn(){return [this](){return turn->let_act();};}
function<void()> puyoPlayPuyo::get_let_drop(){return [this](){return drop->let_act();};}

vector<future_puyo> puyoPlayPuyo::get_future_puyo(puyoBoard& board)
{
    future_puyo fp1; 
    fp1.x = round(x1), fp1.color = color1;
    for(int y = (int)y1 ; y < board.get_board_size().first ; ++y)
        if(puyo_touched(board,round(x1),y+1))
        {
            fp1.y = y;
            break;
        }
    future_puyo fp2; 
    fp2.x = round(x2), fp2.color = color2;
    for(int y = (int)y2 ; y < board.get_board_size().first ; ++y)
        if(puyo_touched(board,round(x2),y+1))
        {
            fp2.y = y;
            break;
        }
    fp2.y += round(y2-y1);//보정
    return {fp1,fp2};
}