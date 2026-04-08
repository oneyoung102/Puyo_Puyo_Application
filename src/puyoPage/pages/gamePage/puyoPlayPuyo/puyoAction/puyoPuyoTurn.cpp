#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoPuyoTurn.hpp"

#include "puyoPuyoLeft.hpp"
#include "puyoPuyoRight.hpp"
#include "puyoPuyoUp.hpp"


#include <cmath>

using namespace std;

bool puyoPuyoTurn::test(puyoBoard& board, puyoPlayPuyo& puyo)
{
    const auto[x1,y1,x2,y2] = puyo.get_pos();
    if(round(x1) == round(x2))
    {
        if(y1 < y2)
            return !puyo.touched(board,floor(x1)+1,floor(y1)) && !puyo.touched(board,floor(x1)+1,ceil(y1)) && !puyo.touched(board,ceil(x1)+1,y1) && !puyo.touched(board,floor(x2)+1,y2);
        else if(y1 > y2)
            return !puyo.touched(board,floor(x1)-1,floor(y1)) && !puyo.touched(board,floor(x1)-1,ceil(y1)) && !puyo.touched(board,ceil(x1)-1,y1) && !puyo.touched(board,floor(x2)-1,y2);
    }
    else if(round(y1) == round(y2))
    {
        if(x1 > x2)
            return !puyo.touched(board,x1,floor(y1)+1) && !puyo.touched(board,x1,ceil(y1)+1) && !puyo.touched(board,x2,floor(y2)+1);
        else if(x1 < x2)
            return !puyo.touched(board,x1,floor(y1)-1) && !puyo.touched(board,x1,ceil(y1)-1) && !puyo.touched(board,x2,floor(y2)-1);
    }
    return false;
}
bool puyoPuyoTurn::decline(puyoBoard& board,puyoPlayPuyo& puyo)
{
    if(act_count == 0)
    {
        tie(start_x1, start_y1, start_x2, start_y2) = puyo.get_pos();
        if(!test(board,puyo))
        {
            const auto[x1,y1,x2,y2] = puyo.get_pos();
            const float left_gap = (round(x1) == floor(x1)) ? 1 : round(x1)-floor(x1),
                        right_gap = (round(x1) == ceil(x1)) ? 1 : ceil(x1)-round(x1),
                        up_gap = (round(y1) == floor(y1)) ? 1 : round(y1)-floor(y1);
            puyoPuyoLeft left(act_count_constant,left_gap);
            puyoPuyoRight right(act_count_constant,right_gap);
            puyoPuyoUp up(act_count_constant,up_gap);
                if(round(x1) == round(x2))
                {
                    if(y1 < y2)
                    {
                        left.let();
                        if(left.decline(board,puyo))
                            sub_act = std::move(make_unique<puyoPuyoLeft>(act_count_constant,left_gap));
                    }
                    else if(y1 > y2)
                    {
                        right.let();
                        if(right.decline(board,puyo))
                            sub_act = std::move(make_unique<puyoPuyoRight>(act_count_constant,right_gap));
                    }
                }
                else if(round(y1) == round(y2))
                {
                    /*if(x1 < x2 && down.decline_act(board,puyo))
                        sub_act = new puyoPuyoDown(act_count_constant,1);
                    */
                    if(x1 > x2)
                    {
                        up.let();
                        if(up.decline(board,puyo))
                            sub_act = std::move(make_unique<puyoPuyoUp>(act_count_constant,up_gap));
                    }
                }
            if(sub_act != nullptr) 
            {
                sub_act->let();
                return true;
            }
            act_count = -1;
            return false;
        }
    }
    return true;
}

void puyoPuyoTurn::arrive(puyoPlayPuyo& puyo, float x1,float y1,float x2,float y2)
{
    if(round(start_x1) == round(start_x2))
        puyo.move(round(x1),y1,round(x2),y1);
    if(round(start_y1) == round(start_y2))
    {
        if(start_x1 > start_x2)
            puyo.move(round(x1),y1,round(x1),y1+1);
        else if(start_x1 < start_x2)
            puyo.move(round(x1),y1,round(x1),y1-1);

    }
}

puyoPuyoTurn::puyoPuyoTurn(int amount, float degree) : puyoPuyoAct(amount){this->degree = degree;}

void puyoPuyoTurn::act(puyoPlayPuyo& puyo)
{
    if(sub_act != nullptr) 
        sub_act->act(puyo);
    const auto[x1,y1,x2,y2] = puyo.get_pos();
    if(act_count == act_count_constant)
    {
        arrive(puyo,x1,y1,x2,y2);
        halt();
        return;
    }
    const float rad = (degree * M_PI / 180.0f) / act_count_constant;
    const float c = cos(rad), s = sin(rad);

    float dx = x2 - x1;
    float dy = y2 - y1;
    puyo.move(x1,y1, x1 + dx*c - dy*s, y1 + dx*s + dy*c);
    ++act_count;
};

void puyoPuyoTurn::let(){
    if(!acting())
    {
        act_count = 0;
        sub_act = nullptr;
    }
}