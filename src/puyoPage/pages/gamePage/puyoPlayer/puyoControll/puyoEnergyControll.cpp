#include "puyoPage/pages/gamePage/puyoPlayer/puyoControll/puyoEnergyControll.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoAction/puyoPuyoFly.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"

using namespace std;
using namespace puyoImageConstant;
using namespace puyoGameConstant;

puyoEnergyControll::puyoEnergyControll(){};


const vector<puyoPuyo> &puyoEnergyControll::get() const { return energy_puyos; }
void puyoEnergyControll::fly(const puyoBoard& board)
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
void puyoEnergyControll::spawn(int from_player_num, int to_player_num)
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

void puyoEnergyControll::add(puyoPuyo&& temp_energy_puyo)
{
    temp_energy_puyos.push_back(std::move(temp_energy_puyo));
}
void puyoEnergyControll::add(std::vector<puyoPuyo>&& temp_energy_puyos)
{
    for(auto& temp_energy_puyo : temp_energy_puyos)
        add(std::move(temp_energy_puyo));
}
bool puyoEnergyControll::empty() const {return temp_energy_puyos.empty();}
void puyoEnergyControll::clear() { temp_energy_puyos.clear(); }