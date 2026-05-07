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
        const auto puyo_type = energy_puyo.get_type();  
        const auto type = puyo_type.get();
        switch(type)
        {
            case _puyoType::Type::blue :
            case _puyoType::Type::red :
            case _puyoType::Type::yellow :
            case _puyoType::Type::green :
            case _puyoType::Type::pupple :
                print_16x16(w,ENERGY_PUYO_POS+POSi(CASTi(type),0),pos+energy_puyo.get_pos());
                break;
            default :
                break;
        }
    }
}