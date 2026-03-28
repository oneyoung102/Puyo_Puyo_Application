#include <SFML/Graphics.hpp>
#include "puyoPrintEnergyPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoTempPuyo/puyoEnergyPuyo.hpp"

#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

#include <vector>

using namespace puyoImageConstant;
using namespace std;
using namespace sf;

puyoPrintEnergyPuyo::puyoPrintEnergyPuyo(vector<puyoEnergyPuyo>& ep, Sprite puyo, int x, int y, int life) : puyoPrintObject(puyo,x,y,life), energy_puyos(ep){}


void puyoPrintEnergyPuyo::print_object(RenderWindow& w)
{
    for(auto& energy_puyo : energy_puyos)
    {
        const auto puyo = energy_puyo.get_puyo_color();
        const auto [px,py]= energy_puyo.get_puyo_pos();      
        switch(puyo)
        {
            case puyoType::blue :
            case puyoType::red :
            case puyoType::yellow :
            case puyoType::green :
            case puyoType::pupple :
                print_16x16(w,ENERGY_PUYO_X+(int)puyo,ENERGY_PUYO_Y,x+px,y+py);
                break;
            default :
                break;
        }
    }
}