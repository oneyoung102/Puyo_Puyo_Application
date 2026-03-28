#include <SFML/Graphics.hpp>
#include "puyoPrintVanishPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoType.hpp"
#include "puyoPage/pages/gamePage/puyoTempPuyo/puyoVanishPuyo.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

#include <vector>

using namespace puyoImageConstant;
using namespace std;
using namespace sf;

puyoPrintVanishPuyo::puyoPrintVanishPuyo(vector<puyoVanishPuyo>& vp, Sprite puyo, int x, int y, int life) : puyoPrintObject(puyo,x,y,life), vanish_puyos(vp){}


void puyoPrintVanishPuyo::print_object(RenderWindow& w)
{
    for(auto& vanish_puyo : vanish_puyos)
    {
        auto [px,py] = vanish_puyo.get_puyo_pos();
        px = x + PUYO_SIZE*px;
        py = y + PUYO_SIZE*py;
        const auto puyo = vanish_puyo.get_puyo_color();
        switch(puyo)
        {
            case puyoType::blank :
                break;
            case puyoType::obstruct :
            case puyoType::tiny_bomb :
            case puyoType::mid_bomb :
            case puyoType::big_bomb :
            case puyoType::danger_bomb :
                print_16x16(w,VANISH_OTHER_X,VANISH_OTHER_Y,px,py);
                break;
            default :
                if(vanish_puyo.vanish_stay())
                    print_16x16(w,VANISH_STAY_PUYO_X+2*(int)puyo,VANISH_STAY_PUYO_Y,px,py);
                else if(vanish_puyo.vanish_soon())
                    print_16x16(w,VANISH_SOON_PUYO_X+2*(int)puyo,VANISH_SOON_PUYO_Y,px,py);
                else
                    print_16x16(w,VANISH_SOON_PUYO_X+2*(int)puyo+1,VANISH_SOON_PUYO_Y,px,py);
                break;
        }
    }
}