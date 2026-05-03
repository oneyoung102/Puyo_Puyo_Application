#include <SFML/Graphics.hpp>
#include "puyoPrintEnergyPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"

#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"
#include "puyoTool/puyoCast.hpp"

#include <vector>

using namespace puyoImageConstant;
using namespace std;
using namespace sf;

puyoPrintEnergyPuyo::puyoPrintEnergyPuyo(const vector<puyoPuyo>& energy_puyos, Sprite puyo, int life)
    : puyoPrintObject(puyo,life)
    , energy_puyos(energy_puyos)
{}


void puyoPrintEnergyPuyo::print(RenderWindow& w)
{
    for(auto& energy_puyo : energy_puyos)
    {
        const auto puyo = energy_puyo.get_type();  
        switch(puyo)
        {
            case puyoType::blue :
            case puyoType::red :
            case puyoType::yellow :
            case puyoType::green :
            case puyoType::pupple :
                print_16x16(w,ENERGY_PUYO_POS+POSi(CASTi(puyo),0),pos+energy_puyo.get_pos());
                break;
            default :
                break;
        }
    }
}