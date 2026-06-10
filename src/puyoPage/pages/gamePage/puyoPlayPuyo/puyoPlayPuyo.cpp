#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"

#include "puyoPage/pages/gamePage/puyoPuyo/puyoAction/puyoPuyoAct.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoAction/puyoPuyoFourWayMove.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoAction/puyoPuyoTurn.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoAction/puyoPuyoGravity.hpp"

#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"

#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/puyoType.hpp"

#include <memory>


using namespace std;
using namespace puyoGameConstant;

puyoPlayPuyo::puyoPlayPuyo(const pair<puyoPuyo,puyoPuyo>& types, int gravity_value, int stay_value)
    : puyoObjectSignal()
    , gravity_value(gravity_value)
    , stay_value(stay_value)
    , stay(0)
    , down_taken(false)
    , drop_taken(false)
{
    for(size_t i = 0 ; i < 2 ; ++i)
    {
        gravity[i] = make_unique<puyoPuyoGravity>(gravity_value);
        gravity[i]->let();
    }

    play_puyo[0] = types.first;
    play_puyo[1] = types.second;
}


void puyoPlayPuyo::act_let(const puyoBoard& board)
{
    if(play_puyo[0].have_act() && !play_puyo[0].acting() 
    || play_puyo[1].have_act() && !play_puyo[1].acting())
    {
        for(auto& puyo : play_puyo)
            puyo.set_act();
        down_taken = false;
        return;
    }
    for(auto& puyo : play_puyo)
        if(puyo.have_act() && !puyo.decide(board))
            return;
    for(auto& puyo : play_puyo)
        if(puyo.have_act())
            puyo.only_act_let();
}

void puyoPlayPuyo::gravity_let(const puyoBoard& board)
{
    if(sat(board) && stay < stay_value)
    {
        if(stay == 0)
            for(size_t i = 0 ; i < 2 ; ++i)
            {
                const auto[x,y] = play_puyo[i].get_pos();
                play_puyo[i].move({round(x),round(y)});
            }
        ++stay;
    }
    else if(gravity[0]->decide(board, play_puyo[0]) && gravity[1]->decide(board, play_puyo[1]))
    {
        gravity[0]->act(play_puyo[0]);
        gravity[1]->act(play_puyo[1]);
        stay = 0;
    }
}

bool puyoPlayPuyo::down() const {return down_taken;}
bool puyoPlayPuyo::dropped() const
{
    return (!gravity[0]->acting() || !gravity[1]->acting()) || drop_taken;
}

vector<puyoPuyo> puyoPlayPuyo::to_gravity_puyo(const puyoBoard& board)
{
    const int tick = sat(board) ? BOARD_FALL_GRAVITY_TICK : PLAYPUYO_DROP_GRAVITY_TICK;
    play_puyo[0].set_act(make_unique<puyoPuyoGravity>(tick));
    play_puyo[1].set_act(make_unique<puyoPuyoGravity>(tick));
    vector<puyoPuyo> temp_play_puyo;
    temp_play_puyo.push_back(std::move(play_puyo[0]));
    temp_play_puyo.push_back(std::move(play_puyo[1]));
    return temp_play_puyo;
}
const puyoPuyo& puyoPlayPuyo::get_each(size_t number) const {return play_puyo[number];}
const decltype(puyoPlayPuyo::play_puyo)& puyoPlayPuyo::get() const {return play_puyo;}

pair<POSf,POSf> puyoPlayPuyo::get_pos() const
{
    return {play_puyo[0].get_pos(),play_puyo[1].get_pos()};
}
pair<puyoType::Type,puyoType::Type> puyoPlayPuyo::get_type() const
{
    const auto type1 = play_puyo[0].get_type(), type2 = play_puyo[1].get_type();
    return {type1,type2};
}

bool puyoPlayPuyo::sat(const puyoBoard& board) const
{
    for(auto& puyo : play_puyo)
    {
        const auto[x,y] = puyo.get_pos();
        if(board.touched(POSi(round(x), floor(y)+1)))
            return true;
    }
    return false;
}
bool puyoPlayPuyo::moving() const
{
    for(const auto& puyo : play_puyo)
        if(puyo.acting())
            return true;
    return false;
}

void puyoPlayPuyo::let_fourway(Direction dir)
{
    if(moving())
        return;
    for(auto& puyo : play_puyo)
    {
        puyo.set_act(make_unique<puyoPuyoFourWayMove>(PLAYPUYO_FOURWAYMOVE_TICK,DIR[dir]));
        puyo.let();
    }
}
void puyoPlayPuyo::let_left(){let_fourway(LEFT);}
void puyoPlayPuyo::let_right(){let_fourway(RIGHT);}
void puyoPlayPuyo::let_down()
{
    let_fourway(DOWN);
    if(moving())
        down_taken = true;
}
void puyoPlayPuyo::let_turn()
{
    if(moving())
        return;
    play_puyo[1].set_act(make_unique<puyoPuyoTurn>(PLAYPUYO_TURN_TICK,play_puyo[0],play_puyo[1].get_pos()));
    play_puyo[1].let();
}
void puyoPlayPuyo::let_drop()
{
    if(moving()
)
        return;
    drop_taken = true;
}