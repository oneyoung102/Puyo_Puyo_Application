#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoAction/puyoPuyoAct.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include "puyoPuyoTurn.hpp"

#include "puyoPage/pages/gamePage/puyoPuyo/puyoAction/puyoPuyoFourWayMove.hpp"


#include <cmath>

using namespace std;

bool puyoPuyoTurn::test(puyoBoard& board, puyoPuyo& puyo)
{
    const auto[x,y] = puyo.get_pos();
    switch(dir)
    {
        case Direction::UP :
            return !board.touched(floor(y),x-1) && !board.touched(ceil(y),x-1) && !board.touched(y+1,x-1);
        case Direction::DOWN :
            return !board.touched(floor(y),x+1) && !board.touched(ceil(y),x+1) && !board.touched(y-1,x+1) ;
        case Direction::RIGHT :
            return !board.touched(floor(y)-1,x) && !board.touched(ceil(y)-1,x) && !board.touched(floor(y)-1,x-1);
        case Direction::LEFT :
            return !board.touched(floor(y)+1,x) && !board.touched(ceil(y)+1,x) && !board.touched(ceil(y)+1,x+1);
    }
    return false;
}
bool puyoPuyoTurn::decline(puyoBoard& board,puyoPuyo& puyo)
{
    if(act_count == 0)
    {
        if(test(board,puyo))
            return true;
        else
        {
            const auto[x,y] = puyo.get_pos();
            array<unique_ptr<puyoPuyoFourWayMove>,2> acts;
            for(int i = 0 ; i < 2 ; ++i)
            {
                switch(dir)
                {
                    case Direction::UP :
                        acts[i] = std::move(make_unique<puyoPuyoFourWayMove>(get_act_count_init(),make_pair(1,0)));
                        break;
                    case Direction::DOWN :
                        acts[i] = std::move(make_unique<puyoPuyoFourWayMove>(get_act_count_init(),make_pair(-1,0)));
                        break;
                    case Direction::RIGHT :
                        acts[i] = std::move(make_unique<puyoPuyoFourWayMove>(get_act_count_init(),make_pair(0,1)));
                        break;
                    case Direction::LEFT :
                        acts[i] = std::move(make_unique<puyoPuyoFourWayMove>(get_act_count_init(),make_pair(0,-1)));
                        break;
                }
                acts[i]->let();
            }
            if(acts[0]->decline(board,puyo) && acts[1]->decline(board,center))
            {
                sub_acts[0] = std::move(acts[0]);
                sub_acts[1] = std::move(acts[1]);
                return true;
            }
        }
    }
    else if(acting())
        return true;
    halt();
    arrive(puyo);
    return false;
}

void puyoPuyoTurn::arrive(puyoPuyo& puyo)
{
    const auto[center_x,center_y] = center.get_pos();
    switch(dir)
    {
        case Direction::UP :
            puyo.move(center_x-1,center_y);
            break;
        case Direction::DOWN :
            puyo.move(center_x+1,center_y);
            break;
        case Direction::RIGHT :
            puyo.move(center_x,center_y-1);
            break;
        case Direction::LEFT :
            puyo.move(center_x,center_y+1);
            break;
    }
}

puyoPuyoTurn::puyoPuyoTurn(int amount, puyoPuyo& center, std::pair<float,float> turning)
    : puyoPuyoAct(amount)
    , rad(-M_PI/2/act_count_init), c(cos(rad)),s(sin(rad))//시계 반대방향
    , center(center)
{
    const auto[x,y] = turning;
    const auto[center_x,center_y] = center.get_pos();
    if(round(center_x) == round(x))
        dir = (y < center_y) ? Direction::UP : Direction::DOWN;
    else if(round(center_y) == round(y))
        dir = (x < center_x) ? Direction::LEFT : Direction::RIGHT;
}

void puyoPuyoTurn::act(puyoPuyo& puyo)
{
    const auto[x,y] = puyo.get_pos();
    const auto[center_x,center_y] = center.get_pos();
    const float dx = x-center_x, dy = y-center_y;
    puyo.move(center_x + dx*c - dy*s, center_y + dx*s + dy*c);
    if(sub_acts[0] && sub_acts[1]) 
    {
        sub_acts[0]->act(puyo);
        sub_acts[1]->act(center);
    } 
    ++act_count;
};