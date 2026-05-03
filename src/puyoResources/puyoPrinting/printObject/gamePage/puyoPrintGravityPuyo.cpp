#include <SFML/Graphics.hpp>
#include "puyoPrintGravityPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

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
        const auto type = gravity_puyo.get_type();
        const auto screen_pos = pos+gravity_puyo.get_pos()*PUYO_SIZE;
        switch(type)
        {
            case puyoType::blue :
            case puyoType::red :
            case puyoType::yellow :
            case puyoType::green :
            case puyoType::pupple :
            {
                if(gravity_puyo.get_tick() <= puyoGameConstant::GRAVITY_TICK_STANDARD)//dropping
                {
                    print_16x16(w,DROPPING_PUYO_POS+POSi(static_cast<int>(type),0),screen_pos-POSf(0,PUYO_SIZE));
                    print_16x16(w,DROPPING_PUYO_POS+POSi(static_cast<int>(type),1),screen_pos);
                }
                else//gravity
                    print_16x16(w,GRAVITY_PUYO_POS+POSi(static_cast<int>(type),0),screen_pos);
                break;
            }
            default :
                print_puyo(w,type,screen_pos);
                break;
        }
    }
}