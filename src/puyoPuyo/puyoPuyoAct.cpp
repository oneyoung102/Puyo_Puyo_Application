#include "puyoPuyoAct.hpp"

#include <tuple>
#include <cmath>

bool puyoPuyoAct::is_acting(){return act_count != -1;}
puyoPuyoAct::puyoPuyoAct(int amount) : act_count_constant(amount){act_count = -1;}
void puyoPuyoAct::arrive(puyoPuyo& puyo, float x1,float y1,float x2,float y2)
{
    puyo.move_puyo(round(x1),start_y1+round(y1-start_y1),
                    round(x2),start_y2+round(y2-start_y2));
}
bool puyoPuyoAct::decline_act(puyoBoard& board,puyoPuyo& puyo)
{
    if(act_count == 0)
    {
        tie(start_x1, start_y1, start_x2, start_y2) = puyo.get_puyo_pos();
        if(!test_act(board,puyo))
        {
            halt_act();
            return false;
        }
    }
    return true;
}
void puyoPuyoAct::let_act(){if(!is_acting()) act_count = 0;}
void puyoPuyoAct::halt_act(){act_count = -1;}
