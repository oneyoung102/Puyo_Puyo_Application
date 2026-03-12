#include <SFML/Graphics.hpp>
#include "puyoPrintVanishPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoTempPuyo/puyoVanishPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

using namespace puyoImageConstant;
using namespace sf;

puyoPrintVanishPuyo::puyoPrintVanishPuyo(vector<puyoVanishPuyo>& vp, Sprite puyo, int x, int y, int life) : puyoPrintObject(puyo,x,y,life), vanish_puyos(vp){}


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
            if(vanish_puyo.vanish_stay())
                print_puyo(w,VANISH_STAY_PUYO_X+2*puyo,VANISH_STAY_PUYO_Y,px,py);
            else if(vanish_puyo.vanish_soon())
                print_puyo(w,VANISH_SOON_PUYO_X+2*puyo,VANISH_SOON_PUYO_Y,px,py);
            else
                print_puyo(w,VANISH_SOON_PUYO_X+2*puyo+1,VANISH_SOON_PUYO_Y,px,py);
        }
    }
}