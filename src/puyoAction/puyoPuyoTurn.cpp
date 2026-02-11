#include "../puyoBoard.hpp"
#include "../puyoPlayPuyo.hpp"
#include "puyoPuyoTurn.hpp"

#include "puyoPuyoLeft.hpp"
#include "puyoPuyoRight.hpp"
#include "puyoPuyoUp.hpp"


#include <cmath>

using namespace std;

bool puyoPuyoTurn::test_act(puyoBoard& board, puyoPlayPuyo& puyo)
{
    const auto[x1,y1,x2,y2] = puyo.get_puyo_pos();
    if(round(x1) == round(x2))
    {
        if(y1 > y2)
            return !puyo.puyo_touched(board,floor(x1)+1,floor(y1)) && !puyo.puyo_touched(board,floor(x1)+1,ceil(y1)) && !puyo.puyo_touched(board,ceil(x1)+1,y1) && !puyo.puyo_touched(board,floor(x2)+1,y2);
        else if(y1 < y2)
            return !puyo.puyo_touched(board,floor(x1)-1,floor(y1)) && !puyo.puyo_touched(board,floor(x1)-1,ceil(y1)) && !puyo.puyo_touched(board,ceil(x1)-1,y1) && !puyo.puyo_touched(board,floor(x2)-1,y2);
    }
    else if(round(y1) == round(y2))
    {
        if(x1 < x2)
            return !puyo.puyo_touched(board,x1,floor(y1)+1) && !puyo.puyo_touched(board,x1,ceil(y1)+1) && !puyo.puyo_touched(board,x2,floor(y2)+1);
        else if(x1 > x2)
            return !puyo.puyo_touched(board,x1,floor(y1)-1) && !puyo.puyo_touched(board,x1,ceil(y1)-1) && !puyo.puyo_touched(board,x2,floor(y2)-1);
    }
    return false;
}
bool puyoPuyoTurn::decline_act(puyoBoard& board,puyoPlayPuyo& puyo)
{
    if(act_count == 0)
    {
        tie(start_x1, start_y1, start_x2, start_y2) = puyo.get_puyo_pos();
        if(!test_act(board,puyo))
        {
            const auto[x1,y1,x2,y2] = puyo.get_puyo_pos();
            const float left_gap = (x1 == floor(x1)) ? 1 : x1-floor(x1),
                        right_gap = (ceil(x1) == x1) ? 1 : ceil(x1)-x1,
                        up_gap = (y1 == floor(y1)) ? 1 : y1-floor(y1);
            puyoPuyoLeft left(act_count_constant,left_gap);
            puyoPuyoRight right(act_count_constant,right_gap);
            puyoPuyoUp up(act_count_constant,up_gap);
                if(round(x1) == round(x2))
                {
                    if(y1 > y2)
                    {
                        left.let_act();
                        if(left.decline_act(board,puyo))
                            sub_act = new puyoPuyoLeft(act_count_constant,left_gap);
                    }
                    else if(y1 < y2)
                    {
                        right.let_act();
                        if(right.decline_act(board,puyo))
                            sub_act = new puyoPuyoRight(act_count_constant,right_gap);
                    }
                }
                else if(round(y1) == round(y2))
                {
                    /*if(x1 > x2 && down.decline_act(board,puyo))
                        sub_act = new puyoPuyoDown(act_count_constant,1);
                    */
                    if(x1 < x2)
                    {
                        up.let_act();
                        if(up.decline_act(board,puyo))
                            sub_act = new puyoPuyoUp(act_count_constant,up_gap);
                    }
                }
            if(sub_act != nullptr) 
            {
                sub_act->let_act();
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
        puyo.move_puyo(round(x1),y1,round(x2),y1);
    if(round(start_y1) == round(start_y2))
    {
        if(start_x1 < start_x2)
            puyo.move_puyo(round(x1),y1,round(x1),y1+1);
        if(start_x1 > start_x2)
            puyo.move_puyo(round(x1),y1,round(x1),y1-1);

    }
}

puyoPuyoTurn::puyoPuyoTurn(int amount, float d) : puyoPuyoAct(amount){degree = d;}

void puyoPuyoTurn::act_puyo(puyoPlayPuyo& puyo)
{
    if(sub_act != nullptr) 
        sub_act->act_puyo(puyo);
    const auto[x1,y1,x2,y2] = puyo.get_puyo_pos();
    if(act_count == act_count_constant)
    {
        arrive(puyo,x1,y1,x2,y2);
        halt_act();
        return;
    }
    const float rad = (degree * M_PI / 180.0f) / act_count_constant;
    const float c = cos(rad), s = sin(rad);

    float dx = x2 - x1;
    float dy = y2 - y1;
    puyo.move_puyo(x1,y1, x1 + dx*c - dy*s, y1 + dx*s + dy*c);
    ++act_count;
};

void puyoPuyoTurn::let_act(){
    if(!is_acting())
    {
        act_count = 0;
        sub_act = nullptr;
    }
}