#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"
#include <SFML/Graphics.hpp>
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

using namespace puyoImageConstant;
using namespace sf;

puyoPrintObject::puyoPrintObject(Sprite s, float xx, float yy, int l) : sprite(s)
{
    life = l; // life == -1 일 때는 영생
    x = xx;
    y = yy;
}

bool puyoPrintObject::is_alive(){return life != 0;}

void puyoPrintObject::print_puyo(RenderWindow& w, int img_x, int img_y, int px, int py)
{
    img_x = PUYO_SIZE*img_x, img_y = PUYO_SIZE*img_y;
    sprite.setTextureRect(IntRect({img_x, img_y}, {PUYO_SIZE, PUYO_SIZE})); 
    print_sprite(w,px,py);
}

void puyoPrintObject::print_sprite(RenderWindow& window, float x1, float y1)
{
    sprite.setPosition({x1, y1});
    window.draw(sprite);
    if(is_alive())
        --life;
}
void puyoPrintObject::print_object(RenderWindow& w)
{
    print_sprite(w,x,y);
}
