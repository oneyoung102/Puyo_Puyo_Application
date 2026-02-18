#include <SFML/Graphics.hpp>
#include "puyoPrintFuturePuyo.hpp"
#include "../../../puyoPage/gamePage/puyoTempPuyo/puyoFuturePuyo.hpp"
#include "../../puyoImageConstant.hpp"

using namespace puyoImageConstant;

puyoPrintFuturePuyo::puyoPrintFuturePuyo(vector<puyoFuturePuyo>& fp, Sprite puyo, int x, int y, int life) : puyoPrintObject(puyo,x,y,life), future_puyos(fp)
{
    sprite.setColor(Color(255, 255, 255, 128*FUTURE_PUYO_ALPHA_VALUE));//투명도 조절
}

void puyoPrintFuturePuyo::print_puyo(RenderWindow& w, int img_x, int img_y, int px, int py)
{
    img_x = PUYO_SIZE*img_x, img_y = PUYO_SIZE*img_y;
    sprite.setTextureRect(IntRect({img_x, img_y}, {PUYO_SIZE, PUYO_SIZE})); 
    print_sprite(w,px,py);
}

void puyoPrintFuturePuyo::print_object(RenderWindow& w)
{
    for(auto&& future_puyo : future_puyos)
    {
        const int color = future_puyo.get_puyo_color();
        const auto [px,py] = future_puyo.get_puyo_pos();
        print_puyo(w,0,color,x+PUYO_SIZE*px,y +PUYO_SIZE*py);
    }
}