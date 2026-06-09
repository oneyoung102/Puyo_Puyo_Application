#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"
#include <SFML/Graphics.hpp>
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"
#include "puyoTool/puyoCast.hpp"

using namespace puyoImageConstant;
using namespace sf;

puyoPrintObject::puyoPrintObject(Sprite s, const POSf& pos, int life) : sprite(s)
{
    this->life = life; // life == -1 일 때는 영생
    this->pos = pos;
}
puyoPrintObject::puyoPrintObject(Sprite s, int life) : sprite(s)
{
    this->life = life; // life == -1 일 때는 영생
    pos = POSf();
}

bool puyoPrintObject::alive() const {return life != 0;}
bool puyoPrintObject::is_immortal() const {return life == PRINT_IMMORTAL;}

void puyoPrintObject::print_16x16(RenderWindow& w, const POSi& img_pos, const POSf& screen_pos)
{
    sprite.setTextureRect(IntRect({img_pos.x*PUYO_SIZE,img_pos.y*PUYO_SIZE}, {PUYO_SIZE, PUYO_SIZE})); 
    print_sprite(w,screen_pos);
}
void puyoPrintObject::print_puyo(RenderWindow& w, const puyoPuyo& puyo, const POSf& screen_pos)
{
    if(puyo.empty())
        return;
    if(puyo.is_frozen())
    {
        print_16x16(w,FROZEN_PUYO_POS,screen_pos);
        return;
    }
    switch(puyo.get_type())
    {
        case puyoType::Type::wall : 
            print_16x16(w,WALL_PUYO_POS,screen_pos);
            break;
        case puyoType::Type::obstruct : 
            print_16x16(w,OBSTRUCT_PUYO_POS,screen_pos);
            break;
        case puyoType::Type::bomb :
        {
            const int idx = CASTi(puyo.get_type_state())-CASTi(puyoType::typeState::explode_stay1);
            print_16x16(w,BOMB_POS+POSi(idx,0),screen_pos);
            break;
        }
        default ://일반 색깔 뿌요
            if(puyo.is_charged())
                print_16x16(w,CHARGED_PUYO_POS+POSi(CASTi(puyo.get_type()),0),screen_pos);
            else 
                print_16x16(w,POSi(0,CASTi(puyo.get_type())),screen_pos);
            break;
    }
}

void puyoPrintObject::print_sprite(RenderWindow& window, const POSf& screen_pos)
{
    sprite.setPosition(Vector2f(screen_pos.x,screen_pos.y));
    window.draw(sprite);
    if(alive())
        --life;
}
void puyoPrintObject::print(RenderWindow& w)
{
    print_sprite(w,pos);
}
