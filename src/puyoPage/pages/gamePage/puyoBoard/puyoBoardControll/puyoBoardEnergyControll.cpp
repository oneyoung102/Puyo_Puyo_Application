#include "puyoPage/pages/gamePage/puyoBoard/puyoBoardControll/puyoBoardEnergyControll.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

using namespace std;
using namespace puyoImageConstant;

puyoBoardEnergyControll::puyoBoardEnergyControll(){};


vector<puyoEnergyPuyo> &puyoBoardEnergyControll::get_energy_puyos() { return energy_puyos; }
bool puyoBoardEnergyControll::temp_energy_puyo_empty() {return temp_energy_puyos.empty();}
void puyoBoardEnergyControll::fly_energy_puyos(puyoBoard& board)
{
    for (int i = 0; i < energy_puyos.size();)
        if (energy_puyos[i].fly_stopped())
        {
            std::swap(energy_puyos[i], energy_puyos.back());
            energy_puyos.pop_back();
        }
        else
        {
            energy_puyos[i].fly_let(board);
            ++i;
        }
}
void puyoBoardEnergyControll::find_energy_puyos(float fx, float fy, float tx, float ty)
{
    if (temp_energy_puyos.empty())
        return;
    for (const auto [x, y, color] : temp_energy_puyos)
        energy_puyos.push_back(puyoEnergyPuyo(
            fx + x * PUYO_SIZE, fy + y * PUYO_SIZE, tx, ty, color, puyoGameConstant::BOARD_FLY_TICK));
    temp_energy_puyos.clear();
}

void puyoBoardEnergyControll::add_temp_energy_puyo(std::tuple<int,int,puyoType> temp_energy_puyo)
{
    temp_energy_puyos.push_back(temp_energy_puyo);
}
void puyoBoardEnergyControll::clear_temp_energy_puyos() { temp_energy_puyos.clear(); }