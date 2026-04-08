#include "puyoPage/pages/gamePage/puyoBoard/puyoBoardControll/puyoBoardEnergyControll.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoAction/puyoPuyoFly_temp.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

using namespace std;
using namespace puyoImageConstant;

puyoBoardEnergyControll::puyoBoardEnergyControll(){};


vector<puyoPuyo> &puyoBoardEnergyControll::get() { return energy_puyos; }
bool puyoBoardEnergyControll::temp_empty() {return temp_energy_puyos.empty();}
void puyoBoardEnergyControll::fly(puyoBoard& board)
{
    for (int i = 0; i < energy_puyos.size();)
        if(!energy_puyos[i].acting())
        {
            std::swap(energy_puyos[i], energy_puyos.back());
            energy_puyos.pop_back();
        }
        else
        {
            energy_puyos[i].act_let(board);
            ++i;
        }
}
void puyoBoardEnergyControll::find(float fx, float fy, float tx, float ty)
{
    if (temp_energy_puyos.empty())
        return;
    for (const auto [x, y, type] : temp_energy_puyos)
    {
        energy_puyos.push_back(puyoPuyo(fx + x * PUYO_SIZE, fy + y * PUYO_SIZE, type));
        energy_puyos.back().change_act(make_unique<puyoPuyoFly_temp>(fx + x * PUYO_SIZE, fy + y * PUYO_SIZE, tx, ty, puyoGameConstant::BOARD_FLY_TICK));
        energy_puyos.back().let();
    }
    temp_energy_puyos.clear();
}

void puyoBoardEnergyControll::temp_add(std::tuple<int,int,puyoType> temp_energy_puyo)
{
    temp_energy_puyos.push_back(temp_energy_puyo);
}
void puyoBoardEnergyControll::temp_clear() { temp_energy_puyos.clear(); }