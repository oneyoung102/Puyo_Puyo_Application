#include "puyoPage/pages/gamePage/puyoPlayer/puyoBoardControll/puyoBoardEnergyControll.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoAction/puyoPuyoFly.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"

using namespace std;
using namespace puyoImageConstant;
using namespace puyoGameConstant;

puyoBoardEnergyControll::puyoBoardEnergyControll(){};


const vector<puyoPuyo> &puyoBoardEnergyControll::get() const { return energy_puyos; }
void puyoBoardEnergyControll::fly(const puyoBoard& board)
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
void puyoBoardEnergyControll::to_energy_puyo(int from_player_num, int to_player_num)
{
    if(temp_energy_puyos.empty())
        return;
    for (auto& energy_puyo : temp_energy_puyos)
    {
        const POSf& screen_pos = PLAYER_BOARD_POS[from_player_num]+energy_puyo.get_pos()*PUYO_SIZE;
        energy_puyo.set_act(make_unique<puyoPuyoFly>(BOARD_FLY_TICK,screen_pos,OBSTRUCT_VIEWER_POS[to_player_num]-screen_pos));
        energy_puyos.push_back(std::move(energy_puyo));
        energy_puyos.back().let();
    }
    temp_energy_puyos.clear();
}

void puyoBoardEnergyControll::add_temp(const puyoPuyo& temp_energy_puyo)
{
    temp_energy_puyos.push_back(temp_energy_puyo);
}
void puyoBoardEnergyControll::add_temp(const std::vector<puyoPuyo>& temp_energy_puyos)
{
    for(const auto& temp_energy_puyo : temp_energy_puyos)
        add_temp(temp_energy_puyo);
}
bool puyoBoardEnergyControll::empty_temp() const {return temp_energy_puyos.empty();}
void puyoBoardEnergyControll::clear_temp() { temp_energy_puyos.clear(); }