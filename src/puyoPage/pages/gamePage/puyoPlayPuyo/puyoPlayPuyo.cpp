#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"

#include "puyoAction/puyoPuyoAct.hpp"
#include "puyoAction/puyoPuyoLeft.hpp"
#include "puyoAction/puyoPuyoRight.hpp"
#include "puyoAction/puyoPuyoDown.hpp"
#include "puyoAction/puyoPuyoUp.hpp"
#include "puyoAction/puyoPuyoTurn.hpp"
#include "puyoAction/puyoPuyoDrop.hpp"
#include "puyoAction/puyoPuyoGravity.hpp"
#include "puyoAction/puyoPuyoStay.hpp"

#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"

#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoType.hpp"

#include <tuple>
#include <utility>
#include <memory>
#include <algorithm>


using namespace std;
using namespace puyoGameConstant;

puyoPlayPuyo::puyoPlayPuyo(pair<float,float> spawn_pos, pair<puyoType,puyoType> types, int gravity_value, int stay_value) : puyoObjectSignal()
{

    action = nullptr;
    gravity  = make_unique<puyoPuyoGravity>(gravity_value,PLAYPUYO_FALL_GRAVITY_DISTANCE); 
    stay  = make_unique<puyoPuyoStay>(stay_value,PLAYPUYO_STAY_BONUS);

    acts.emplace_back(make_unique<puyoPuyoLeft>(PLAYPUYO_LEFT_TICK,PLAYPUYO_LEFT_DISTANCE));
    acts.emplace_back(make_unique<puyoPuyoRight>(PLAYPUYO_RIGHT_TICK,PLAYPUYO_RIGHT_DISTANCE));
    acts.emplace_back(make_unique<puyoPuyoDown>(PLAYPUYO_DOWN_TICK,PLAYPUYO_DOWN_DISTANCE));
    //acts.emplace_back(make_unique<puyoPuyoUp>(PLAYPUYO_UP_TICK,PLAYPUYO_UP_DISTANCE));
    acts.emplace_back(make_unique<puyoPuyoTurn>(PLAYPUYO_TURN_TICK,PLAYPUYO_TURN_DEGREE));
    acts.emplace_back(make_unique<puyoPuyoDrop>(PLAYPUYO_LEFT_DISTANCE));

    tie(x1,y1) = spawn_pos;
    --spawn_pos.second; tie(x2,y2) = spawn_pos;
    tie(type1,type2) = types;

    down_let_is_taken = false;
}


void puyoPlayPuyo::act_let(puyoBoard& board)
{
    if(action == nullptr)
    {
        for(auto&& act : acts)//행동 찾기
            if(act->acting() && act->decline(board,*this))
            {
                if(act == acts[(int)Act_type::down])
                    down_let_is_taken = true;
                action = act;
                set_signal(puyoPlayPuyoSignal::puyo_move);
                break;
            }
    }
    else
    {
        /*for(auto act : acts)//현재 행동 중에 들어오는 행동 무시
            if(action != act && act->is_acting())
                act->halt_act();*/
        if(action->acting())
            action->act(*this);
        else
            action = nullptr;
    }
}

void puyoPlayPuyo::gravity_let(puyoBoard& board)
{
    //if(action == nullptr)//뿌요가 움직일 때는 하강 안 함
    {
        if(gravity->decline(board,*this))
            gravity->act(*this);
    }
    if(stay->decline(board,*this))
    {
        stay->act(*this);
        if(action != nullptr)
            stay->more_stay();
    }
}
bool puyoPlayPuyo::down(){return exchange(down_let_is_taken,false);}
bool puyoPlayPuyo::dropped()
{
    return action == nullptr && stay->broken()
                    || acts[(unsigned int)Act_type::drop]->acting();
}
bool puyoPlayPuyo::holding(){return !gravity->acting();}

int puyoPlayPuyo::get_drop_height(puyoBoard& board)
{
    const auto[board_r,board_c] = board.get_size();
    const int iy1 = y1, iy2 = y2;
    for(int dy = 1 ; dy < board_r ; ++dy)
        if(!board.in(iy1+dy,x1) || touched(board,x1,iy1+dy)
        || !board.in(iy2+dy,x2) || touched(board,x2,iy2+dy))
            return dy-1;
    return 0;
}

vector<PUYO_INFO> puyoPlayPuyo::to_gravity_puyo()
{
    if(y1 < y2)//y좌표가 큰 게 먼저 오게
    {
        swap(x1,x2);
        swap(y1,y2);
        swap(type1,type2);
    }
    return {
        {x1, y1, type1,PLAYPUYO_DROP_GRAVITY_TICK},
        {x2, y2, type2,PLAYPUYO_DROP_GRAVITY_TICK}
    };
}

bool puyoPlayPuyo::touched(puyoBoard& board, int ix, int iy)
{
    return iy >= 0 && (!board.in(iy,ix) || board.get_puyo(iy,ix) != puyoType::blank)
        || iy < 0 && !board.in_col(ix);
}

tuple<float,float,float,float> puyoPlayPuyo::get_pos(){return make_tuple(x1,y1,x2,y2);}
void puyoPlayPuyo::move(float to_x1, float to_y1, float to_x2, float to_y2)
{
    x1 = to_x1;
    y1 = to_y1;
    x2 = to_x2;
    y2 = to_y2;
}
pair<puyoType,puyoType> puyoPlayPuyo::get_types(){return make_pair(type1,type2);}

void puyoPlayPuyo::let_left(){acts[(unsigned int)puyoPlayPuyo::Act_type::left]->let();}
void puyoPlayPuyo::let_right(){acts[(unsigned int)puyoPlayPuyo::Act_type::right]->let();}
void puyoPlayPuyo::let_down(){acts[(unsigned int)puyoPlayPuyo::Act_type::down]->let();}
//void puyoPlayPuyo::let_up(){acts[]->let_act();}
void puyoPlayPuyo::let_turn(){acts[(unsigned int)puyoPlayPuyo::Act_type::turn]->let();}
void puyoPlayPuyo::let_drop(){acts[(unsigned int)puyoPlayPuyo::Act_type::drop]->let();}

bool puyoPlayPuyo::is_moving(){return action != nullptr;}