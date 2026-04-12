#include "puyoPage/pages/gamePage/puyoBoard/puyoBoardControll/puyoBoardEnergyControll.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoAction/puyoPuyoFly.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

using namespace std;
using namespace puyoImageConstant;

puyoBoardEnergyControll::puyoBoardEnergyControll(){};


const vector<puyoPuyo> &puyoBoardEnergyControll::get() { return energy_puyos; }
bool puyoBoardEnergyControll::empty_temp() const {return temp_energy_puyos.empty();}
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
void puyoBoardEnergyControll::find(std::pair<float,float> from_pos, std::pair<float,float> to_pos)
{
    if (temp_energy_puyos.empty())
        return;
    const auto[fx,fy] = from_pos;
    const auto[tx,ty] = to_pos;
    for (const auto [x, y, type, tick] : temp_energy_puyos)
    {
        energy_puyos.push_back(puyoPuyo(fx+x*PUYO_SIZE, fy+y*PUYO_SIZE, type
                    , make_unique<puyoPuyoFly>(make_pair(fx+x*PUYO_SIZE, fy+y*PUYO_SIZE),make_pair(tx, ty), tick)));
        energy_puyos.back().let();
    }
    temp_energy_puyos.clear();
}

void puyoBoardEnergyControll::add_temp(PUYO_INFO temp_energy_puyo)
{
    temp_energy_puyos.push_back(temp_energy_puyo);
}
void puyoBoardEnergyControll::clear_temp() { temp_energy_puyos.clear(); }