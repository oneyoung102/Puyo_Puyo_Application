#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoAction/puyoPuyoAct.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include "puyoPuyoTurn.hpp"

#include "puyoPage/pages/gamePage/puyoPuyo/puyoAction/puyoPuyoFourWayMove.hpp"


#include <cmath>

using namespace std;

bool puyoPuyoTurn::test(const puyoBoard& board, puyoPuyo& puyo)
{
    const auto[x,y] = puyo.get_pos();
    bool able = false;
    switch(turn_dir)
    {
        case Direction::LEFT :
            able = !board.touched(POSi(x-1, y)) && !board.touched(POSi(x-1, ceil(y))) && !board.touched(POSi(x-1, ceil(y)+1));
            break;
        case Direction::RIGHT :
            able = !board.touched(POSi(x+1, y)) && !board.touched(POSi(x+1, ceil(y))) && !board.touched(POSi(x+1, y-1));
            break;
        case Direction::UP :
            able = !board.touched(POSi(x, y-1)) && !board.touched(POSi(x, ceil(y)-1)) && !board.touched(POSi(x-1, y-1));
            break;
        case Direction::DOWN :
            able = !board.touched(POSi(x, y+1)) && !board.touched(POSi(x, ceil(y)+1)) && !board.touched(POSi(x+1, ceil(y)+1));
            break;
    }
    if(able)
        return true;
////// 반작용
    array<unique_ptr<puyoPuyoFourWayMove>,2> acts;
    for(int i = 0 ; i < 2 ; ++i)
    {
        switch(turn_dir)
        {
            case Direction::LEFT :
                acts[i] = std::move(make_unique<puyoPuyoFourWayMove>(get_act_count_init(),POSf(1,0)));
                break;
            case Direction::RIGHT :
                acts[i] = std::move(make_unique<puyoPuyoFourWayMove>(get_act_count_init(),POSf(-1,0)));
                break;
            case Direction::UP :
                acts[i] = std::move(make_unique<puyoPuyoFourWayMove>(get_act_count_init(),POSf(0,1)));
                break;
            case Direction::DOWN :
                acts[i] = std::move(make_unique<puyoPuyoFourWayMove>(get_act_count_init(),POSf(0,-1)));
                break;
        }
        acts[i]->let();
    }
    if(acts[0]->decide(board,puyo) && acts[1]->decide(board,center))
    {
        sub_acts = std::move(acts);
        return true;
    }
    return false;
}

void puyoPuyoTurn::arrive(puyoPuyo& puyo)
{
    const auto[center_x,center_y] = center.get_pos();
    switch(turn_dir)
    {
        case Direction::LEFT :
            puyo.move({center_x-1,center_y});
            break;
        case Direction::RIGHT :
            puyo.move({center_x+1,center_y});
            break;
        case Direction::UP :
            puyo.move({center_x,center_y-1});
            break;
        case Direction::DOWN :
            puyo.move({center_x,center_y+1});
            break;
    }
}

puyoPuyoTurn::puyoPuyoTurn(int amount, puyoPuyo& center, POSf turning)
    : puyoPuyoAct(amount)
    , rad(-M_PI/2/act_count_init), c(cos(rad)),s(sin(rad))//시계 반대방향
    , center(center)
{
    const auto[x,y] = turning;
    const auto[center_x,center_y] = center.get_pos();
    if(round(center_x) == round(x)) // 어느 방향으로 회전할지
        turn_dir = (y < center_y) ? Direction::LEFT : Direction::RIGHT;
    else if(round(center_y) == round(y))
        turn_dir = (x < center_x) ? Direction::DOWN : Direction::UP;
}

void puyoPuyoTurn::act(puyoPuyo& puyo)
{
    const auto[center_x,center_y] = center.get_pos();
    const POSf dpos = puyo.get_pos()-center.get_pos();
    puyo.move({center_x + dpos.x*c - dpos.y*s, center_y + dpos.x*s + dpos.y*c});
    if(sub_acts[0] && sub_acts[1]) 
    {
        sub_acts[0]->act(puyo);
        sub_acts[1]->act(center);
    } 
    ++act_count;
};