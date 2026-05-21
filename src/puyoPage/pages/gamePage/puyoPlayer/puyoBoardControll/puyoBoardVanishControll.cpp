#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include "puyoPage/pages/gamePage/puyoPhase/puyoPhase.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoPlayer/puyoBoardControll/puyoBoardVanishControll.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoAction/puyoPuyoVanish.hpp"
#include <memory>
#include <queue>
#include <utility>

#include "puyoTool/puyoDir.hpp"

using namespace std;

puyoBoardVanishControll::puyoBoardVanishControll(){}

void puyoBoardVanishControll::add(const puyoPuyo& puyo)
{
    vanish_puyos.push_back(puyo);
    vanish_puyos.back().let();
}


const vector<puyoPuyo> &puyoBoardVanishControll::get() const { return vanish_puyos; }
bool puyoBoardVanishControll::empty() const { return vanish_puyos.empty(); }

void puyoBoardVanishControll::vanish(puyoBoard& board)
{
    for (int i = 0; i < vanish_puyos.size();)
        if(!vanish_puyos[i].acting())
        {
            std::swap(vanish_puyos[i], vanish_puyos.back());
            vanish_puyos.pop_back();
            board.set_signal(puyoBoardSignal::vanished);
        }
        else
        {
            vanish_puyos[i].act_let(board);
            ++i;
        }
}

puyoPuyo puyoBoardVanishControll::to_vanish_puyo_each(puyoBoard& board, const POSs& pos)
{
    const auto puyo = board.get_puyo(pos);
    if(puyo.is_frozen())
    {
        board.ref_puyo(pos).unfreeze();
        board.set_signal(puyoBoardSignal::unfreeze);
        return board.get_puyo(pos);
    }
    else 
    {
        board.remove_puyo(pos);
        return puyo;
    }
}
tuple<int,int,vector<puyoPuyo>> puyoBoardVanishControll::fire_cluster(const puyoBoard& board, const POSs& fire_pos, vector<vector<bool>>& visited) const
{
    int color_puyo_count = 0, weight_sum = 0;
    vector<puyoPuyo> stored_puyos;
    queue<POSs> coords;
    const auto& puyo = board.get_puyo(fire_pos);
    
    coords.push(fire_pos);
    while(!coords.empty())
    {
        const auto pos = coords.front();
        coords.pop();
        if(visited[pos.r][pos.c])
            continue;
        visited[pos.r][pos.c] = true;

        const auto& curr_puyo = board.get_puyo(pos);
        stored_puyos.push_back(curr_puyo);
        
        if(curr_puyo.is_colored())
            ++color_puyo_count;
        weight_sum += curr_puyo.get_weight();

        for(const auto& dpos: DIR)
        {
            const auto npos = pos+dpos;
            if (!board.in(npos))
                continue;
            const auto& npuyo = board.get_puyo(npos);
            if (curr_puyo.is_linkable(npuyo) && !visited[npos.r][npos.c])
                coords.push(npos);
        }
    }
    return make_tuple(color_puyo_count, weight_sum, stored_puyos);
}
tuple<int, vector<int>, vector<puyoType::Type>, vector<puyoPuyo>> puyoBoardVanishControll::to_vanish_puyo(puyoBoard& board)
{
    int puyo_count = 0;
    vector<int> link_count;
    vector<puyoType::Type> color_count;
    vector<puyoPuyo> temp_energy_puyos;

    const auto bsize = board.get_size();
    vector<vector<bool>> visited(bsize.r, vector<bool>(bsize.c, false));
    for (size_t i = 0; i < bsize.r; ++i)
        for (size_t j = 0; j < bsize.c; ++j)
        {
            if(visited[i][j])
                continue;
            
            const auto& curr_puyo = board.get_puyo({j, i});
            if(!curr_puyo.is_colored())
                continue;
            const auto& [color_puyo_count, weight_sum, stored_puyos] = fire_cluster(board,{j, i}, visited);
            if(weight_sum >= condition_for_vanish)
            {
                puyo_count += color_puyo_count;
                link_count.push_back(color_puyo_count);
                color_count.push_back(curr_puyo.get_type());
                for(auto& puyo : stored_puyos)
                {
                    temp_energy_puyos.push_back(to_vanish_puyo_each(board,puyo.get_pos()));
                    const int tick = puyo.is_same(puyoType::Type::obstruct) ? puyoGameConstant::BOARD_OBSTRUCT_VANISH_TICK : puyoGameConstant::BOARD_BASIC_VANISH_TICK;
                    auto temp_puyo = std::move(puyo);
                    temp_puyo.set_act(make_unique<puyoPuyoVanish>(tick));
                    add(temp_puyo);
                }
            }
    }
    return make_tuple(puyo_count, link_count, color_count, temp_energy_puyos);
}
void puyoBoardVanishControll::set_condition(int amount){condition_for_vanish = amount;}
int puyoBoardVanishControll::get_condition() const { return condition_for_vanish; }