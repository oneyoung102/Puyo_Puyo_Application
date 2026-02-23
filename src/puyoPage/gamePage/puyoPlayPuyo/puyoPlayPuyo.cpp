#include "../puyoBoard.hpp"

#include "puyoAction/puyoPuyoAct.hpp"
#include "puyoAction/puyoPuyoLeft.hpp"
#include "puyoAction/puyoPuyoRight.hpp"
#include "puyoAction/puyoPuyoDown.hpp"
#include "puyoAction/puyoPuyoUp.hpp"
#include "puyoAction/puyoPuyoTurn.hpp"
#include "puyoAction/puyoPuyoDrop.hpp"
#include "puyoAction/puyoPuyoGravity.hpp"
#include "puyoAction/puyoPuyoStay.hpp"

#include "puyoPlayPuyo.hpp"

#include "../puyoTempPuyo/puyoGravityPuyo.hpp"

#include <tuple>
#include <utility>
#include <memory>
#include <algorithm>


using namespace std;

puyoPlayPuyo::puyoPlayPuyo(pair<float,float> spawn_pos, pair<int,int> color, int g, int s) : puyoObjectSignal()
{

    action = nullptr;
    gravity  = make_unique<puyoPuyoGravity>(g,1); 
    stay  = make_unique<puyoPuyoStay>(s,110);

    acts.emplace_back(make_unique<puyoPuyoLeft>(400,1));
    acts.emplace_back(make_unique<puyoPuyoRight>(400,1));
    acts.emplace_back(make_unique<puyoPuyoDown>(400,1));
    //acts.emplace_back(make_unique<puyoPuyoUp>(400,1));
    acts.emplace_back(make_unique<puyoPuyoTurn>(360,-90));
    acts.emplace_back(make_unique<puyoPuyoDrop>(-1));

    tie(x1,y1) = spawn_pos;
    tie(x2,y2) = make_pair(spawn_pos.first,spawn_pos.second-1);
    tie(color1,color2) = color;

    taken_down_let = false;

    gravity_value = 150;//드롭 이후에 중력 상수
}


void puyoPlayPuyo::act_let(puyoBoard& board)
{
    if(action == nullptr)
    {
        for(auto&& act : acts)//행동 찾기
            if(act->is_acting() && act->decline_act(board,*this))
            {
                if(act == acts[(int)Act_type::down])
                    taken_down_let = true;
                action = act;
                signals[(int)puyoPlayPuyoSignal::puyo_move] = true;
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
}

void puyoPlayPuyo::gravity_let(puyoBoard& board)
{
    //if(action == nullptr)//뿌요가 움직일 때는 하강 안 함
    {
        if(gravity->decline_act(board,*this))
            gravity->act_puyo(*this);
    }
    if(stay->decline_act(board,*this))
    {
        stay->act_puyo(*this);
        if(action != nullptr)
            stay->more_stay();
    }
}
bool puyoPlayPuyo::is_down(){return exchange(taken_down_let,false);}
bool puyoPlayPuyo::is_dropped()
{
    return action == nullptr && stay->is_destroyed()
                    || acts[(unsigned int)Act_type::drop]->is_acting();
}
bool puyoPlayPuyo::is_holding(){return !gravity->is_acting();}

int puyoPlayPuyo::get_drop_height(puyoBoard& board)
{
    const auto[board_r,board_c] = board.get_board_size();
    int iy1 = y1, iy2 = y2;
    for(int dy = 1 ; dy < board_r ; ++dy)
        if(!board.is_in_board(iy1+dy,x1) || puyo_touched(board,x1,iy1+dy)
        || !board.is_in_board(iy2+dy,x2) || puyo_touched(board,x2,iy2+dy))
            return dy;
    return 0;
}

vector<puyoGravityPuyo> puyoPlayPuyo::to_gravity_puyo()
{
    if(y1 < y2)//y좌표가 큰 게 먼저 오게
    {
        swap(x1,x2);
        swap(y1,y2);
        swap(color1,color2);
    }
    vector<puyoGravityPuyo> v;
    v.emplace_back(x1, y1, color1,gravity_value);
    v.emplace_back(x2, y2, color2,gravity_value);
    return v;
}

bool puyoPlayPuyo::puyo_touched(puyoBoard& board, int ix, int iy)
{
    return iy >= 0 && (!board.is_in_board(iy,ix) || board.get_puyo(iy,ix) != puyoBoard::Type::blank)
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

void puyoPlayPuyo::let_left(){acts[(unsigned int)puyoPlayPuyo::Act_type::left]->let_act();}
void puyoPlayPuyo::let_right(){acts[(unsigned int)puyoPlayPuyo::Act_type::right]->let_act();}
void puyoPlayPuyo::let_down(){acts[(unsigned int)puyoPlayPuyo::Act_type::down]->let_act();}
//void puyoPlayPuyo::let_up(){acts[]->let_act();}
void puyoPlayPuyo::let_turn(){acts[(unsigned int)puyoPlayPuyo::Act_type::turn]->let_act();}
void puyoPlayPuyo::let_drop(){acts[(unsigned int)puyoPlayPuyo::Act_type::drop]->let_act();}

bool puyoPlayPuyo::is_moving(){return action != nullptr;}