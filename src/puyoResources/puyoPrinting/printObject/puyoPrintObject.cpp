#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"
#include <SFML/Graphics.hpp>
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

using namespace puyoImageConstant;
using namespace sf;

puyoPrintObject::puyoPrintObject(Sprite s, POS pos, int life) : sprite(s)
{
    this->life = life; // life == -1 일 때는 영생
    x = pos.x;
    y = pos.y;
}
puyoPrintObject::puyoPrintObject(Sprite s, int life) : sprite(s)
{
    this->life = life; // life == -1 일 때는 영생
    x = 0;
    y = 0;
}

bool puyoPrintObject::alive(){return life != 0;}

void puyoPrintObject::print_16x16(RenderWindow& w, POS img_pos, Vector2f screen_pos)
{
    sprite.setTextureRect(IntRect({(int)img_pos.x*PUYO_SIZE,(int)img_pos.y*PUYO_SIZE}, {PUYO_SIZE, PUYO_SIZE})); 
    print_sprite(w,screen_pos);
}
void puyoPrintObject::print_puyo(RenderWindow& w, puyoType type, Vector2f screen_pos)
{
    switch(type)
    {
        case puyoType::blank :
            break;
        case puyoType::obstruct : 
            print_16x16(w,{OBSTRUCT_PUYO_X,OBSTRUCT_PUYO_Y},screen_pos);
            break;
        case puyoType::tiny_bomb :
        case puyoType::mid_bomb :
        case puyoType::big_bomb :
        case puyoType::danger_bomb :
            print_16x16(w,POS(BOMB_X-(int)puyoType::tiny_bomb+(int)type,BOMB_Y),screen_pos);
            break;
        default ://일반 색깔 뿌요
            print_16x16(w,POS(0,(int)type),screen_pos);
            break;
    }
}

void puyoPrintObject::print_sprite(RenderWindow& window, Vector2f screen_pos)
{
    sprite.setPosition(screen_pos);
    window.draw(sprite);
    if(alive())
        --life;
}
void puyoPrintObject::print(RenderWindow& w)
{
    print_sprite(w,{x,y});
}
