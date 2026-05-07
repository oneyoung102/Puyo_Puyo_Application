#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"
#include <SFML/Graphics.hpp>
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/puyoType.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"
#include "puyoTool/puyoCast.hpp"

using namespace puyoImageConstant;
using namespace sf;

puyoPrintObject::puyoPrintObject(Sprite s, POSf pos, int life) : sprite(s)
{
    this->life = life; // life == -1 일 때는 영생
    this->pos = pos;
}
puyoPrintObject::puyoPrintObject(Sprite s, int life) : sprite(s)
{
    this->life = life; // life == -1 일 때는 영생
    pos = POSf();
}

bool puyoPrintObject::alive(){return life != 0;}
bool puyoPrintObject::is_immortal(){return life == PRINT_IMMORTAL;}

void puyoPrintObject::print_16x16(RenderWindow& w, POSi img_pos, POSf screen_pos)
{
    img_pos *= PUYO_SIZE;
    sprite.setTextureRect(IntRect({img_pos.x,img_pos.y}, {PUYO_SIZE, PUYO_SIZE})); 
    print_sprite(w,screen_pos);
}
void puyoPrintObject::print_puyo(RenderWindow& w, puyoType type, POSf screen_pos)
{
    if(type.empty())
        return;
    switch(type.get())
    {
        case _puyoType::Type::obstruct : 
            print_16x16(w,OBSTRUCT_PUYO_POS,screen_pos);
            break;
        case _puyoType::Type::bomb :
        {
            const float state = type.get_bomb_state();
            const int idx = (state <= puyoGameConstant::BOMB_UPDATED1)
                            +(state <= puyoGameConstant::BOMB_UPDATED2)
                            +(state <= puyoGameConstant::BOMB_UPDATED3);  
            print_16x16(w,BOMB_POS-POSi(idx,0),screen_pos);
            break;
        }
        default ://일반 색깔 뿌요
            print_16x16(w,POSi(0,CASTi(type.get())),screen_pos);
            break;
    }
}

void puyoPrintObject::print_sprite(RenderWindow& window, POSf screen_pos)
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
