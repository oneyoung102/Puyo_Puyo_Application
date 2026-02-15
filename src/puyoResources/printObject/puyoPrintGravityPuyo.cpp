#include <SFML/Graphics.hpp>
#include "puyoPrintGravityPuyo.hpp"
#include "../../puyoPhase/puyoTempPuyo/puyoGravityPuyo.hpp"
#include "../puyoPrinting.hpp"

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
        const int color = gravity_puyo.get_puyo_color();
        auto [px,py]= gravity_puyo.get_puyo_pos();
        px = x + PUYO_SIZE*px;
        py = y + PUYO_SIZE*py;
        print_puyo(w,GRAVITY_PUYO_X+color,GRAVITY_PUYO_Y,px,py);
        print_puyo(w,GRAVITY_PUYO_X+color,GRAVITY_PUYO_Y+1,px,py);
    }
}