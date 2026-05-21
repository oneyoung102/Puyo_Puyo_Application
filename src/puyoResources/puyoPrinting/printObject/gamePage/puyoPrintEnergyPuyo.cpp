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
    for(const auto& energy_puyo : energy_puyos)
    {
        const auto type = energy_puyo.get_type();
        switch(type)
        {
            case puyoType::Type::blue :
            case puyoType::Type::red :
            case puyoType::Type::yellow :
            case puyoType::Type::green :
            case puyoType::Type::pupple :
                print_16x16(w,ENERGY_PUYO_POS+POSi(CASTi(type),0),pos+energy_puyo.get_pos());
                break;
            default :
                break;
        }
    }
}