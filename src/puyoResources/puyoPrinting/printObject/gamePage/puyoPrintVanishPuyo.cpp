#include <SFML/Graphics.hpp>
#include "puyoPrintVanishPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/puyoType.hpp"
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
        const auto puyo_type = vanish_puyo.get_type();
        const auto type = puyo_type.get();
        if(puyo_type.is_frozen())
        {
            const float prop = vanish_puyo.get_state();
            if(prop <= puyoGameConstant::VANISH_STAY_PROP)
                print_16x16(w,FROZEN_PUYO_POS+POSi(1,0),screen_pos);
            else
                print_16x16(w,FROZEN_PUYO_POS+POSi(2,0),screen_pos);
            continue;
        }
        switch(type)
        {
            case _puyoType::Type::obstruct :
            case _puyoType::Type::bomb :
                print_16x16(w,VANISH_OTHER_POS,screen_pos);
                break;
            default : //색 뿌요
            {
                const float prop = vanish_puyo.get_state();
                if(prop <= puyoGameConstant::VANISH_STAY_PROP)
                    print_16x16(w,VANISH_STAY_PUYO_POS+POSi(2*CASTi(type),0),screen_pos);
                else if(prop <= puyoGameConstant::VANISH_SOON_PROP)
                    print_16x16(w,VANISH_SOON_PUYO_POS+POSi(2*CASTi(type),0),screen_pos);
                else
                    print_16x16(w,VANISH_SOON_PUYO_POS+POSi(2*CASTi(type)+1,0),screen_pos);
                break;
            }
        }
    }
}