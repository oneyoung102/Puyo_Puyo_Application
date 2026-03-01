#include "../puyoBoard.hpp"

#include "puyoTempPuyo.hpp"

#include <tuple>

using namespace std;

puyoTempPuyo::puyoTempPuyo(float xx, float yy, int c)
{  
    x = xx;
    y = yy;
    color = c;
}
bool puyoTempPuyo::puyo_touched(puyoBoard& board, int ix, int iy)
{
    return iy >= 0 && (!board.is_in_board(iy,ix) || board.get_puyo(iy,ix) != puyoBoard::Type::blank)
        || iy < 0 && !board.is_in_col(ix);
}
tuple<float,float> puyoTempPuyo::get_puyo_pos(){return make_tuple(x,y);}
void puyoTempPuyo::move_puyo(float to_x, float to_y)
{
    x = to_x;
    y = to_y;
}
int puyoTempPuyo::get_puyo_color(){return color;}