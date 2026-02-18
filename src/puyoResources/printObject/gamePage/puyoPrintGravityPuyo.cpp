#include <SFML/Graphics.hpp>
#include "puyoPrintGravityPuyo.hpp"
#include "../../../puyoPage/gamePage/puyoTempPuyo/puyoGravityPuyo.hpp"
#include "../../../puyoPage/gamePage/puyoBoard.hpp"

#include "../../puyoImageConstant.hpp"

using namespace puyoImageConstant;

puyoPrintGravityPuyo::puyoPrintGravityPuyo(vector<puyoGravityPuyo>& gp, Sprite puyo, int x, int y, int life) : puyoPrintObject(puyo,x,y,life), gravity_puyos(gp){}

void puyoPrintGravityPuyo::print_puyo(RenderWindow& w, int img_x, int img_y, int px, int py)
{
    img_x = PUYO_SIZE*img_x, img_y = PUYO_SIZE*img_y;
    sprite.setTextureRect(IntRect({img_x, img_y}, {PUYO_SIZE, PUYO_SIZE})); 
    print_sprite(w,px,py);
}

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
            if(gravity_puyo.is_fast())
            {
                print_puyo(w,GRAVITY_PUYO_X+puyo,GRAVITY_PUYO_Y,px,py);
                print_puyo(w,GRAVITY_PUYO_X+puyo,GRAVITY_PUYO_Y+1,px,py-1);
            }
            else
                print_puyo(w,0,puyo,px,py);
        }
    }
}