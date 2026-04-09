#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"
#include <SFML/Graphics.hpp>
#include "puyoPage/pages/gamePage/puyoBoard/puyoType.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

using namespace puyoImageConstant;
using namespace sf;

puyoPrintObject::puyoPrintObject(Sprite s, double x, double y, int life) : sprite(s)
{
    this->life = life; // life == -1 일 때는 영생
    this->x = x;
    this->y = y;
}

bool puyoPrintObject::alive(){return life != 0;}

void puyoPrintObject::print_16x16(RenderWindow& w, int img_x, int img_y, int px, int py)
{
    img_x = PUYO_SIZE*img_x, img_y = PUYO_SIZE*img_y;
    sprite.setTextureRect(IntRect({img_x, img_y}, {PUYO_SIZE, PUYO_SIZE})); 
    print_sprite(w,px,py);
}
void puyoPrintObject::print_puyo(RenderWindow& w, puyoType type, int px, int py)
{
    switch(type)
    {
        case puyoType::blank :
            break;
        case puyoType::obstruct : 
            print_16x16(w,OBSTRUCT_PUYO_X,OBSTRUCT_PUYO_Y,px,py);
            break;
        case puyoType::tiny_bomb :
        case puyoType::mid_bomb :
        case puyoType::big_bomb :
        case puyoType::danger_bomb :
            print_16x16(w,BOMB_X-(int)puyoType::tiny_bomb+(int)type,BOMB_Y,px,py);
            break;
        default ://일반 색깔 뿌요
            print_16x16(w,0,(int)type,px,py);
            break;
    }
}

void puyoPrintObject::print_sprite(RenderWindow& window, double x1, double y1)
{
    sprite.setPosition({(float)x1, (float)y1});
    window.draw(sprite);
    if(alive())
        --life;
}
void puyoPrintObject::print(RenderWindow& w)
{
    print_sprite(w,x,y);
}
