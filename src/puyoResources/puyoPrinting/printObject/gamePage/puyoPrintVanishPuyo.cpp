#include <SFML/Graphics.hpp>
#include "puyoPrintVanishPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

#include <vector>

using namespace puyoImageConstant;
using namespace std;
using namespace sf;

puyoPrintVanishPuyo::puyoPrintVanishPuyo(const vector<puyoPuyo>& vanish_puyos, Sprite puyo, std::pair<float,float> pos, int life)
    : puyoPrintObject(puyo,pos,life)
    , vanish_puyos(vanish_puyos){}


void puyoPrintVanishPuyo::print(RenderWindow& w)
{
    for(auto& vanish_puyo : vanish_puyos)
    {
        auto [px,py] = vanish_puyo.get_pos();
        px = x + PUYO_SIZE*px;
        py = y + PUYO_SIZE*py;
        const auto puyo = vanish_puyo.get_type();
        switch(puyo)
        {
            case puyoType::blank :
                break;
            case puyoType::obstruct :
            case puyoType::tiny_bomb :
            case puyoType::mid_bomb :
            case puyoType::big_bomb :
            case puyoType::danger_bomb :
                print_16x16(w,{VANISH_OTHER_X,VANISH_OTHER_Y},{px,py});
                break;
            default :
            {
                const float prop = vanish_puyo.get_state();
                if(prop <= puyoGameConstant::VANISH_STAY_PROP)
                    print_16x16(w,{VANISH_STAY_PUYO_X+2*(int)puyo,VANISH_STAY_PUYO_Y},{px,py});
                else if(prop <= puyoGameConstant::VANISH_SOON_PROP)
                    print_16x16(w,{VANISH_SOON_PUYO_X+2*(int)puyo,VANISH_SOON_PUYO_Y},{px,py});
                else
                    print_16x16(w,{VANISH_SOON_PUYO_X+2*(int)puyo+1,VANISH_SOON_PUYO_Y},{px,py});
                break;
            }
        }
    }
}