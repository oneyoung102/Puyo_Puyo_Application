#include <SFML/Graphics.hpp>
#include "puyoPrintGravityPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

#include <vector>

using namespace puyoImageConstant;
using namespace std;
using namespace sf;

puyoPrintGravityPuyo::puyoPrintGravityPuyo(const vector<puyoPuyo>& gravity_puyos, Sprite puyo, std::pair<int,int> pos, int life) : puyoPrintObject(puyo,pos,life), gravity_puyos(gravity_puyos){}


void puyoPrintGravityPuyo::print(RenderWindow& w)
{
    for(auto& gravity_puyo : gravity_puyos)
    {
        const auto puyo = gravity_puyo.get_type();
        auto [px,py]= gravity_puyo.get_pos();
        px = x + PUYO_SIZE*px;
        py = y + PUYO_SIZE*py;
        switch(puyo)
        {
            case puyoType::blue :
            case puyoType::red :
            case puyoType::yellow :
            case puyoType::green :
            case puyoType::pupple :
            {
                if(gravity_puyo.get_tick() <= puyoGameConstant::GRAVITY_TICK_STANDARD)//dropping
                {
                    print_16x16(w,{DROPPING_PUYO_X+(int)puyo,DROPPING_PUYO_Y},{px,py-PUYO_SIZE});
                    print_16x16(w,{DROPPING_PUYO_X+(int)puyo,DROPPING_PUYO_Y+1},{px,py});
                }
                else//gravity
                    print_16x16(w,{GRAVITY_PUYO_X+(int)puyo,GRAVITY_PUYO_Y},{px,py});
                break;
            }
            default :
                print_puyo(w,puyo,{px,py});
                break;
        }
    }
}