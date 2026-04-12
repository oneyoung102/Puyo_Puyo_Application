#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"

#include "puyoPage/pages/gamePage/puyoPuyo/puyoAction/puyoPuyoAct.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoAction/puyoPuyoFourWayMove.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoAction/puyoPuyoTurn.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoAction/puyoPuyoGravity.hpp"

#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"

#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType.hpp"

#include <utility>
#include <memory>


using namespace std;
using namespace puyoGameConstant;

puyoPlayPuyo::puyoPlayPuyo(pair<float,float> spawn_pos, pair<puyoType,puyoType> types, int gravity_value, int stay_value)
    : puyoObjectSignal()
    , gravity_value(gravity_value)
    , stay_value(stay_value)
{
    stay = 0;

    for(int i = 0 ; i < 2 ; ++i)
    {
        gravity[i] = std::move(make_unique<puyoPuyoGravity>(gravity_value));
        gravity[i]->let();
    }

    const auto[x,y] = spawn_pos;
    const auto[type1,type2] = types;
    play_puyo[0] = std::move(make_unique<puyoPuyo>(x,y,type1));
    play_puyo[1] = std::move(make_unique<puyoPuyo>(x,y-1,type2));
    down_taken = false;
    drop_taken = false;
}


void puyoPlayPuyo::act_let(puyoBoard& board)
{
    if(play_puyo[0]->have_act() && !play_puyo[0]->acting() 
    || play_puyo[1]->have_act() && !play_puyo[1]->acting())
    {
        play_puyo[0]->set_act();
        play_puyo[1]->set_act();
        return;
    }
    for(auto& puyo : play_puyo)
        puyo->act_let(board);
}

void puyoPlayPuyo::gravity_let(puyoBoard& board)
{
    if(sat(board) && stay < stay_value)
    {
        if(stay == 0)
            for(int i = 0 ; i < 2 ; ++i)
            {
                const auto[x,y] = play_puyo[i]->get_pos();
                play_puyo[i]->move(round(x),round(y));
            }
        ++stay;
    }
    else if(gravity[0]->decline(board, *play_puyo[0]) && gravity[1]->decline(board, *play_puyo[1]))
    {
        gravity[0]->act(*play_puyo[0]);
        gravity[1]->act(*play_puyo[1]);
    }
}

bool puyoPlayPuyo::down(){return exchange(down_taken,false);}
bool puyoPlayPuyo::dropped(const puyoBoard& board)
{
    return (!gravity[0]->acting() || !gravity[1]->acting()) || drop_taken;
}

int puyoPlayPuyo::get_height(const puyoBoard& board)
{
    const auto[board_r,board_c] = board.get_size();
    
    for(const auto& puyo : play_puyo)
    {
        const auto[x,y] = puyo->get_pos();
        for(int dy = 1 ; dy < board_r ; ++dy)
            if(board.touched(y+dy,x))
                return dy-1;
    }
    return 0;
}
vector<PUYO_INFO> puyoPlayPuyo::to_gravity_puyo(const puyoBoard& board) const
{
    const auto[x1,y1] = play_puyo[0]->get_pos();
    const auto[x2,y2] = play_puyo[1]->get_pos();
    const auto type1 = play_puyo[0]->get_type(), type2 = play_puyo[1]->get_type();
    const int tick = sat(board) ? BOARD_FALL_GRAVITY_TICK : PLAYPUYO_DROP_GRAVITY_TICK;
    return {
        {x1, y1, type1, tick},
        {x2, y2, type2, tick}
    };
}
const std::unique_ptr<puyoPuyo>& puyoPlayPuyo::get_each(size_t number){return play_puyo[number];}
const decltype(puyoPlayPuyo::play_puyo)& puyoPlayPuyo::get(){return play_puyo;}

tuple<float,float,float,float> puyoPlayPuyo::get_pos() const
{
    const auto[x1,y1] = play_puyo[0]->get_pos();
    const auto [x2,y2] = play_puyo[1]->get_pos();
    return make_tuple(x1,y1,x2,y2);
}
std::pair<puyoType,puyoType> puyoPlayPuyo::get_type() const
{
    const auto type1 = play_puyo[0]->get_type(), type2 = play_puyo[1]->get_type();
    return make_pair(type1,type2);
}

bool puyoPlayPuyo::sat(const puyoBoard& board) const
{
    for(auto& puyo : play_puyo)
    {
        const auto[x,y] = puyo->get_pos();
        if(board.touched(floor(y)+1,round(x)))
            return true;
    }
    return false;
}
bool puyoPlayPuyo::moving() const
{
    for(auto& puyo : play_puyo)
        if(puyo->acting())
            return true;
    return false;
}

void puyoPlayPuyo::let_left()
{
    if(moving())
        return;
    for(auto& puyo : play_puyo)
    {
        puyo->set_act(make_unique<puyoPuyoFourWayMove>(PLAYPUYO_FOURWAYMOVE_TICK,make_pair(-1,0)));
        puyo->let();
    }
}
void puyoPlayPuyo::let_right()
{
    if(moving())
        return;
    for(auto& puyo : play_puyo)
    {
        puyo->set_act(make_unique<puyoPuyoFourWayMove>(PLAYPUYO_FOURWAYMOVE_TICK,make_pair(1,0)));
        puyo->let();
    }
}
void puyoPlayPuyo::let_down()
{
    if(moving())
        return;
    for(auto& puyo : play_puyo)
    {
        puyo->set_act(make_unique<puyoPuyoFourWayMove>(PLAYPUYO_FOURWAYMOVE_TICK,make_pair(0,1)));
        puyo->let();
    }
    down_taken = true;
}
void puyoPlayPuyo::let_turn()
{
    if(moving())
        return;
    play_puyo[1]->set_act(make_unique<puyoPuyoTurn>(PLAYPUYO_TURN_TICK,*play_puyo[0],play_puyo[1]->get_pos()));
    play_puyo[1]->let();
}
void puyoPlayPuyo::let_drop()
{
    if(moving())
        return;
    drop_taken = true;
}