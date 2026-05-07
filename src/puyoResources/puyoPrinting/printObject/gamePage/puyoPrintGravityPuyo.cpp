#include <SFML/Graphics.hpp>
#include "puyoPrintGravityPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"
#include "puyoTool/puyoCast.hpp"

#include <vector>

using namespace puyoImageConstant;
using namespace std;
using namespace sf;

puyoPrintGravityPuyo::puyoPrintGravityPuyo(const vector<puyoPuyo>& gravity_puyos, Sprite puyo, POSf pos, int life)
: puyoPrintObject(puyo,pos,life)
, gravity_puyos(gravity_puyos)
{}


void puyoPrintGravityPuyo::print(RenderWindow& w)
{
    for(auto& gravity_puyo : gravity_puyos)
    {
        const auto puyo_type = gravity_puyo.get_type();
        const auto type = puyo_type.get();
        const auto screen_pos = pos+gravity_puyo.get_pos()*PUYO_SIZE;
        switch(type)
        {
            case _puyoType::Type::blue :
            case _puyoType::Type::red :
            case _puyoType::Type::yellow :
            case _puyoType::Type::green :
            case _puyoType::Type::pupple :
            {
                if(gravity_puyo.get_tick() <= puyoGameConstant::GRAVITY_TICK_STANDARD)//dropping
                {
                    print_16x16(w,DROPPING_PUYO_POS+POSi(CASTi(type),0),screen_pos-POSf(0,PUYO_SIZE));
                    print_16x16(w,DROPPING_PUYO_POS+POSi(CASTi(type),1),screen_pos);
                }
                else//gravity
                    print_16x16(w,GRAVITY_PUYO_POS+POSi(CASTi(type),0),screen_pos);
                break;
            }
            default :
                print_puyo(w,puyo_type,screen_pos);
                break;
        }
    }
}