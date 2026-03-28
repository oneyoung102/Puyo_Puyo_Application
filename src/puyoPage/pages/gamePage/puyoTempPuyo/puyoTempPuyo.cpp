#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"

#include "puyoPage/pages/gamePage/puyoTempPuyo/puyoTempPuyo.hpp"

#include <utility>

using namespace std;

puyoTempPuyo::puyoTempPuyo(float xx, float yy, puyoType c)
{  
    x = xx;
    y = yy;
    color = c;
}
bool puyoTempPuyo::puyo_touched(puyoBoard& board, int ix, int iy)
{
    return iy >= 0 && (!board.is_in_board(iy,ix) || board.get_puyo(iy,ix) != puyoType::blank)
        || iy < 0 && !board.is_in_col(ix);
}
pair<float,float> puyoTempPuyo::get_puyo_pos(){return make_pair(x,y);}
void puyoTempPuyo::move_puyo(float to_x, float to_y)
{
    x = to_x;
    y = to_y;
}
puyoType puyoTempPuyo::get_puyo_color(){return color;}