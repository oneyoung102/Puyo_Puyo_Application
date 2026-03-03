#include <SFML/Graphics.hpp>
#include "puyoPrintEnergyPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoTempPuyo/puyoEnergyPuyo.hpp"

#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

using namespace puyoImageConstant;

puyoPrintEnergyPuyo::puyoPrintEnergyPuyo(vector<puyoEnergyPuyo>& ep, Sprite puyo, int x, int y, int life) : puyoPrintObject(puyo,x,y,life), energy_puyos(ep){}


void puyoPrintEnergyPuyo::print_object(RenderWindow& w)
{
    for(auto& energy_puyo : energy_puyos)
    {
        const int puyo = energy_puyo.get_puyo_color();
        const auto [px,py]= energy_puyo.get_puyo_pos();
        print_puyo(w,ENERGY_PUYO_X+puyo,ENERGY_PUYO_Y,x+px,y+py);
    }
}