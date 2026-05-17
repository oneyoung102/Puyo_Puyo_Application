#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include "puyoPage/pages/gamePage/puyoPhase/puyoPhase.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoPlayer/puyoBoardControll/puyoBoardVanishControll.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoAction/puyoPuyoVanish.hpp"
#include <queue>
#include <utility>

#include "puyoTool/puyoDir.hpp"

using namespace std;

puyoBoardVanishControll::puyoBoardVanishControll(){}

void puyoBoardVanishControll::add(const PUYO_INFO& puyo)
{
    vanish_puyos.push_back(
        puyoPuyo(std::get<0>(puyo),std::get<1>(puyo),
        make_unique<puyoPuyoVanish>(std::get<2>(puyo))));
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

PUYO_INFO puyoBoardVanishControll::to_vanish_puyo_each(puyoBoard& board, const PUYO_INFO& puyo)
{
    const auto [pos,type,tick] = puyo;
    add(puyo);
    if(type.is_frozen())
    {
        board.ref_puyo(pos).unfreeze();
        board.set_signal(puyoBoardSignal::unfreeze);
    }
    else 
        board.remove_puyo(pos);
    return {pos, type, puyoGameConstant::BOARD_FLY_TICK};
}
tuple<int,int,vector<pair<POSs, puyoType>>> puyoBoardVanishControll::fire_cluster(const puyoBoard& board, POSs fire_pos, vector<vector<bool>>& visited) const
{
    int color_puyo_count, weight_sum = 0;
    vector<pair<POSs, puyoType>> stored_puyos;
    queue<POSs> coords;
    const puyoType puyo = board.get_puyo(fire_pos);
    
    coords.push(fire_pos);
    while(!coords.empty())
    {
        const auto pos = coords.front();
        coords.pop();
        if(visited[pos.r][pos.c])
            continue;
        visited[pos.r][pos.c] = true;

        const puyoType curr_puyo = board.get_puyo(pos);
        stored_puyos.push_back(make_tuple(pos, curr_puyo));
        
        if(curr_puyo.is_colored())
            ++color_puyo_count;
        weight_sum += curr_puyo.get_weight();

        for (const auto& dpos: DIR)
        {
            const auto npos = pos+dpos;
            if (!board.in(npos))
                continue;
            const puyoType npuyo = board.get_puyo(npos);
            if (curr_puyo.is_linkable(npuyo) && !visited[npos.r][npos.c])
                coords.push(npos);
        }
    }
    return make_tuple(color_puyo_count, weight_sum, stored_puyos);
}
tuple<int, vector<int>, vector<_puyoType::Type>, vector<PUYO_INFO>> puyoBoardVanishControll::to_vanish_puyo(puyoBoard& board)
{
    int puyo_count = 0;
    vector<int> link_count;
    vector<_puyoType::Type> color_count;
    vector<PUYO_INFO> temp_energy_puyos;

    const auto bsize = board.get_size();
    vector<vector<bool>> visited(bsize.r, vector<bool>(bsize.c, false));
    for (size_t i = 0; i < bsize.r; ++i)
        for (size_t j = 0; j < bsize.c; ++j)
        {
            if(visited[i][j])
                continue;
            const puyoType puyo = board.get_puyo({j, i});
            if(!puyo.is_colored())
                continue;
            const auto& [color_puyo_count, weight_sum, stored_puyos] = fire_cluster(board,{j, i}, visited);
            if(weight_sum >= condition_for_vanish)
            {
                puyo_count += color_puyo_count;
                link_count.push_back(color_puyo_count);
                color_count.push_back(puyo.get());
                for(const auto& [pos, type] : stored_puyos)
                {
                    const int tick = (type == puyoType(P_OBSTRUCT)) ? puyoGameConstant::BOARD_OBSTRUCT_VANISH_TICK : puyoGameConstant::BOARD_BASIC_VANISH_TICK;
                    temp_energy_puyos.push_back(to_vanish_puyo_each(board,{pos,type,tick}));
                }
            }
    }
    return std::move(make_tuple(puyo_count, std::move(link_count), std::move(color_count), std::move(temp_energy_puyos)));
}
void puyoBoardVanishControll::set_condition(int amount){condition_for_vanish = amount;}
int puyoBoardVanishControll::get_condition() const { return condition_for_vanish; }