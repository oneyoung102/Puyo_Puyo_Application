#include "puyoPrintObject.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

puyoPrintObject::puyoPrintObject(Sprite s, float xx, float yy, int l) : sprite(s)
{
    life = l; // life == -1 일 때는 영생
    x = xx;
    y = yy;
}

bool puyoPrintObject::is_alive(){return life != 0;}

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
