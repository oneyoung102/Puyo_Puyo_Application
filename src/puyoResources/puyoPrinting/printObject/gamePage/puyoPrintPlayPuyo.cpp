#include <SFML/Graphics.hpp>
#include "puyoPrintPlayPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

using namespace puyoImageConstant;

puyoPrintPlayPuyo::puyoPrintPlayPuyo(puyoPlayPuyo& pp, Sprite puyo, int x, int y, int life) : puyoPrintObject(puyo,x,y,life), play_puyo(pp){}

void puyoPrintPlayPuyo::print_object(RenderWindow& w)
{
    const auto [x1,y1,x2,y2] = play_puyo.get_puyo_pos();
    const auto [color1,color2] = play_puyo.get_puyo_color();
    print_puyo(w,0,color1,x + PUYO_SIZE*x1,y + PUYO_SIZE*y1);
    print_puyo(w,0,color2,x + PUYO_SIZE*x2,y + PUYO_SIZE*y2);
}