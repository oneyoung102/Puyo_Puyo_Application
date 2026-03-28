#include <SFML/Graphics.hpp>
#include "puyoPrintGravityPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoTempPuyo/puyoGravityPuyo.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

#include <vector>

using namespace puyoImageConstant;
using namespace std;
using namespace sf;

puyoPrintGravityPuyo::puyoPrintGravityPuyo(vector<puyoGravityPuyo>& gp, Sprite puyo, int x, int y, int life) : puyoPrintObject(puyo,x,y,life), gravity_puyos(gp){}


void puyoPrintGravityPuyo::print_object(RenderWindow& w)
{
    for(auto& gravity_puyo : gravity_puyos)
    {
        const auto puyo = gravity_puyo.get_puyo_color();
        auto [px,py]= gravity_puyo.get_puyo_pos();
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
                if(gravity_puyo.is_fast())//dropping
                {
                    print_16x16(w,DROPPING_PUYO_X+(int)puyo,DROPPING_PUYO_Y,px,py-PUYO_SIZE);
                    print_16x16(w,DROPPING_PUYO_X+(int)puyo,DROPPING_PUYO_Y+1,px,py);
                }
                else//gravity
                    print_16x16(w,GRAVITY_PUYO_X+(int)puyo,GRAVITY_PUYO_Y,px,py);
                break;
            }
            default :
                print_puyo(w,puyo,px,py);
                break;
        }
    }
}