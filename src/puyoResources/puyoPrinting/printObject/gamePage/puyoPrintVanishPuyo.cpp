#include <SFML/Graphics.hpp>
#include "puyoPrintVanishPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"
#include "puyoTool/puyoCast.hpp"

#include <vector>

using namespace puyoImageConstant;
using namespace std;
using namespace sf;

puyoPrintVanishPuyo::puyoPrintVanishPuyo(const vector<puyoPuyo>& vanish_puyos, Sprite puyo, POSf pos, int life)
    : puyoPrintObject(puyo,pos,life)
    , vanish_puyos(vanish_puyos)
{}


void puyoPrintVanishPuyo::print(RenderWindow& w)
{
    for(auto& vanish_puyo : vanish_puyos)
    {
        const auto screen_pos = pos+vanish_puyo.get_pos()*PUYO_SIZE;
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
                print_16x16(w,VANISH_OTHER_POS,screen_pos);
                break;
            default :
            {
                const float prop = vanish_puyo.get_state();
                if(prop <= puyoGameConstant::VANISH_STAY_PROP)
                    print_16x16(w,VANISH_STAY_PUYO_POS+POSi(2*CASTi(puyo),0),screen_pos);
                else if(prop <= puyoGameConstant::VANISH_SOON_PROP)
                    print_16x16(w,VANISH_SOON_PUYO_POS+POSi(2*CASTi(puyo),0),screen_pos);
                else
                    print_16x16(w,VANISH_SOON_PUYO_POS+POSi(2*CASTi(puyo)+1,0),screen_pos);
                break;
            }
        }
    }
}