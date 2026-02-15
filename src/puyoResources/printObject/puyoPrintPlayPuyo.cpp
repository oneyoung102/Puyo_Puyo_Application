#include <SFML/Graphics.hpp>
#include "puyoPrintPlayPuyo.hpp"
#include "../../puyoPhase/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "../puyoPrinting.hpp"

puyoPrintPlayPuyo::puyoPrintPlayPuyo(puyoPlayPuyo& pp, Sprite puyo, int x, int y, int life) : puyoPrintObject(puyo,x,y,life), play_puyo(pp){}

void puyoPrintPlayPuyo::print_puyo(RenderWindow& w, int img_x, int img_y, int px, int py)
{
    img_x = PUYO_SIZE*img_x, img_y = PUYO_SIZE*img_y;
    sprite.setTextureRect(IntRect({img_x, img_y}, {PUYO_SIZE, PUYO_SIZE})); 
    print_sprite(w,px,py);
}

void puyoPrintPlayPuyo::print_object(RenderWindow& w)
{
    const auto [x1,y1,x2,y2] = play_puyo.get_puyo_pos();
    const auto [color1,color2] = play_puyo.get_puyo_color();
    print_puyo(w,0,color1,x + PUYO_SIZE*x1,y + PUYO_SIZE*y1);
    print_puyo(w,0,color2,x + PUYO_SIZE*x2,y + PUYO_SIZE*y2);
}