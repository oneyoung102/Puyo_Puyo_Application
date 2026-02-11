#include "../puyoBoard.hpp"

#include "../puyoAction/puyoPuyoGravity.hpp"
#include "puyoTempPuyo.hpp"

#include <tuple>
#include <utility>
#include <cmath>
#include <functional>


using namespace std;

puyoTempPuyo::puyoTempPuyo(float xx, float yy, int c)
{
    gravity = new puyoPuyoGravity(200);
    x = xx;
    y = yy;
    color = c;
}

bool puyoTempPuyo::deploy_puyo(puyoBoard& board)
{
    const int ix = round(x), iy = round(y);
    if(!board.is_in_board(iy,ix))
        return false;
    board.insert_puyo(color,iy,ix);
    return true;
}

bool puyoTempPuyo::act_gravity(puyoBoard& board) // 
{
    if(gravity->decline_gravity(board,*this))
    {
        gravity->gravity_puyo(*this);
        return true;
    }
    else
        return false;
    return false;
}

bool puyoTempPuyo::puyo_touched(puyoBoard& board, int ix, int iy)
{
    return iy >= 0 && (!board.is_in_board(iy,ix) || board.get_puyo(iy,ix) != -1)
        || iy < 0 && !board.is_in_col(ix);
}

tuple<float,float> puyoTempPuyo::get_puyo_pos(){return make_tuple(x,y);}
void puyoTempPuyo::move_puyo(float to_x, float to_y)
{
    x = to_x;
    y = to_y;
}
int puyoTempPuyo::get_puyo_color(){return color;}
