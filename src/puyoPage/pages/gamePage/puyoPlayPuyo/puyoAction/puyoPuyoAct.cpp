#include "puyoPuyoAct.hpp"
#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"

#include <tuple>
#include <cmath>

using namespace std;

bool puyoPuyoAct::acting(){return act_count != -1;}
puyoPuyoAct::puyoPuyoAct(int amount) : act_count_constant(amount){act_count = -1;}
void puyoPuyoAct::arrive(puyoPlayPuyo& puyo, float x1,float y1,float x2,float y2)
{
    puyo.move(round(x1),y1,
                    round(x2),y2);
}
bool puyoPuyoAct::decline(puyoBoard& board,puyoPlayPuyo& puyo)
{
    if(act_count == 0)
    {
        tie(start_x1, start_y1, start_x2, start_y2) = puyo.get_pos();
        if(!test(board,puyo))
        {
            halt();
            return false;
        }
    }
    return true;
}
void puyoPuyoAct::let(){if(!acting()) act_count = 0;}
void puyoPuyoAct::halt(){act_count = -1;}
