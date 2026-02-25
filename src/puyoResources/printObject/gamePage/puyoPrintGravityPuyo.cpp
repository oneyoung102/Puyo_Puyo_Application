#include <SFML/Graphics.hpp>
#include "puyoPrintGravityPuyo.hpp"
#include "../../../puyoPage/gamePage/puyoTempPuyo/puyoGravityPuyo.hpp"
#include "../../../puyoPage/gamePage/puyoBoard.hpp"

#include "../../puyoImageConstant.hpp"

using namespace puyoImageConstant;

puyoPrintGravityPuyo::puyoPrintGravityPuyo(vector<puyoGravityPuyo>& gp, Sprite puyo, int x, int y, int life) : puyoPrintObject(puyo,x,y,life), gravity_puyos(gp){}


void puyoPrintGravityPuyo::print_object(RenderWindow& w)
{
    for(auto& gravity_puyo : gravity_puyos)
    {
        const int puyo = gravity_puyo.get_puyo_color();
        auto [px,py]= gravity_puyo.get_puyo_pos();
        px = x + PUYO_SIZE*px;
        py = y + PUYO_SIZE*py;
        if(puyo == (int)puyoBoard::Type::obstruct)
            print_puyo(w,OBSTRUCT_PUYO_X,OBSTRUCT_PUYO_Y,px,py);
        else
        {
            if(gravity_puyo.is_fast())//dropping
            {
                print_puyo(w,DROPPING_PUYO_X+puyo,DROPPING_PUYO_Y,px,py);
                print_puyo(w,DROPPING_PUYO_X+puyo,DROPPING_PUYO_Y+1,px,py-1);
            }
            else//gravity
                print_puyo(w,GRAVITY_PUYO_X+puyo,GRAVITY_PUYO_Y,px,py);
        }
    }
}