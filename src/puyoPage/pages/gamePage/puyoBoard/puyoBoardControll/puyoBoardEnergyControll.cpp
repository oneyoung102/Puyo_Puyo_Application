#include "puyoPage/pages/gamePage/puyoBoard/puyoBoardControll/puyoBoardEnergyControll.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoAction/puyoPuyoFly.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"

using namespace std;
using namespace puyoImageConstant;
using namespace puyoGameConstant;

puyoBoardEnergyControll::puyoBoardEnergyControll(){};


const vector<puyoPuyo> &puyoBoardEnergyControll::get() { return energy_puyos; }
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
void puyoBoardEnergyControll::to_energy_puyo(int from_player_num, int to_player_num)
{
    if (temp_energy_puyos.empty())
        return;
    for (const auto [pos, type, tick] : temp_energy_puyos)
    {
        const POSf screen_pos = PLAYER_BOARD_POS[from_player_num]+pos*PUYO_SIZE;
        energy_puyos.push_back(puyoPuyo(screen_pos, type
                    , make_unique<puyoPuyoFly>(screen_pos,OBSTRUCT_VIEWER_POS[to_player_num], tick)));
        energy_puyos.back().let();
    }
    temp_energy_puyos.clear();
}

void puyoBoardEnergyControll::add_temp(PUYO_INFO temp_energy_puyo)
{
    temp_energy_puyos.push_back(temp_energy_puyo);
}
bool puyoBoardEnergyControll::empty_temp() const {return temp_energy_puyos.empty();}
void puyoBoardEnergyControll::clear_temp() { temp_energy_puyos.clear(); }