#include <SFML/Graphics.hpp>
#include "puyoPrintVanishPuyo.hpp"
#include "../../../puyoPage/gamePage/puyoTempPuyo/puyoVanishPuyo.hpp"
#include "../../../puyoPage/gamePage/puyoBoard.hpp"
#include "../../puyoImageConstant.hpp"

using namespace puyoImageConstant;

puyoPrintVanishPuyo::puyoPrintVanishPuyo(vector<puyoVanishPuyo>& vp, Sprite puyo, int x, int y, int life) : puyoPrintObject(puyo,x,y,life), vanish_puyos(vp){}

void puyoPrintVanishPuyo::print_puyo(RenderWindow& w, int img_x, int img_y, int px, int py)
{
    img_x = PUYO_SIZE*img_x, img_y = PUYO_SIZE*img_y;
    sprite.setTextureRect(IntRect({img_x, img_y}, {PUYO_SIZE, PUYO_SIZE})); 
    print_sprite(w,px,py);
}

void puyoPrintVanishPuyo::print_object(RenderWindow& w)
{
    for(auto& vanish_puyo : vanish_puyos)
    {
        auto [px,py] = vanish_puyo.get_puyo_pos();
        px = x + PUYO_SIZE*px;
        py = y + PUYO_SIZE*py;
        const int puyo = vanish_puyo.get_puyo_color();
        if(puyo == (int)puyoBoard::Type::obstruct)
            print_puyo(w,OBSTRUCT_VANISH_PUYO_X,OBSTRUCT_VANISH_PUYO_Y,px,py);
        else
        {
            if(vanish_puyo.vanish_soon())
                print_puyo(w,VANISH_PUYO_X+2*puyo,VANISH_PUYO_Y,px,py);
            else
                print_puyo(w,VANISH_PUYO_X+2*puyo+1,VANISH_PUYO_Y,px,py);
        }
    }
}