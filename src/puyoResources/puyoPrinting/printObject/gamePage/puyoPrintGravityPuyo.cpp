#include <SFML/Graphics.hpp>
#include "puyoPrintGravityPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoTempPuyo/puyoGravityPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"

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
        const int puyo = gravity_puyo.get_puyo_color();
        auto [px,py]= gravity_puyo.get_puyo_pos();
        px = x + PUYO_SIZE*px;
        py = y + PUYO_SIZE*py;
        if(puyo == (int)puyoBoard::Type::obstruct)
            print_puyo(w,OBSTRUCT_PUYO_X,OBSTRUCT_PUYO_Y,px,py);
        else
        {
            if(gravity_puyo.is_fast())//dropping
            {
                print_puyo(w,DROPPING_PUYO_X+puyo,DROPPING_PUYO_Y,px,py-PUYO_SIZE);
                print_puyo(w,DROPPING_PUYO_X+puyo,DROPPING_PUYO_Y+1,px,py);
            }
            else//gravity
                print_puyo(w,GRAVITY_PUYO_X+puyo,GRAVITY_PUYO_Y,px,py);
        }
    }
}