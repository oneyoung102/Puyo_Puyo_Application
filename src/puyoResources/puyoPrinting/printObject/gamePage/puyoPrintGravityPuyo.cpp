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
    for(const auto& gravity_puyo : gravity_puyos)
    {
        const auto& screen_pos = pos+gravity_puyo.get_pos()*PUYO_SIZE;
        const auto type = gravity_puyo.get_type();
        switch(type)
        {
            case puyoType::Type::blue :
            case puyoType::Type::red :
            case puyoType::Type::yellow :
            case puyoType::Type::green :
            case puyoType::Type::pupple :
                if(!gravity_puyo.is_frozen()) //의도적으로 break 안 함
                {
                    if(gravity_puyo.get_tick() <= puyoGameConstant::GRAVITY_TICK_THRESHOLD)//dropping
                    {
                        print_16x16(w,DROPPING_PUYO_POS+POSi(CASTi(type),0),screen_pos-POSf(0,PUYO_SIZE));
                        print_16x16(w,DROPPING_PUYO_POS+POSi(CASTi(type),1),screen_pos);
                    }
                    else//gravity
                        print_16x16(w,GRAVITY_PUYO_POS+POSi(CASTi(type),0),screen_pos);
                    break;
                }
            default :
                print_puyo(w,gravity_puyo,screen_pos);
                break;
        }
    }
}