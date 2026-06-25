#include "puyoPage/pages/gamePage/puyoPhase/puyoPhase.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoPlayer/puyoControll/puyoVanishControll.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoAction/puyoPuyoVanish.hpp"
#include <queue>
#include <utility>

#include "puyoTool/puyoDir.hpp"

using namespace std;

puyoVanishControll::puyoVanishControll(){}

void puyoVanishControll::add(puyoPuyo&& puyo)
{
    vanish_puyos.push_back(std::move(puyo));
    vanish_puyos.back().let();
}


const vector<puyoPuyo> &puyoVanishControll::view() const { return vanish_puyos; }
bool puyoVanishControll::empty() const { return vanish_puyos.empty(); }

void puyoVanishControll::vanish(puyoBoard& board)
{
    for(int i = 0; i < vanish_puyos.size();)
        if(!vanish_puyos[i].acting())
        {
            std::swap(vanish_puyos[i], vanish_puyos.back());
            vanish_puyos.pop_back();
            board.signal(puyoBoardSignal::vanished);
        }
        else
        {
            vanish_puyos[i].act_let(board);
            ++i;
        }
}

tuple<int,int,vector<POSs>> puyoVanishControll::fire_cluster(const puyoBoard& board, const POSs& fire_pos, vector<vector<bool>>& visited) const
{
    int color_puyo_count = 0, weight_sum = 0;
    vector<POSs> stored_puyos;
    queue<POSs> coords;
    const auto& puyo = board.view(fire_pos);
    
    coords.push(fire_pos);
    while(!coords.empty())
    {
        const auto pos = coords.front();
        coords.pop();
        if(visited[pos.r][pos.c])
            continue;
        visited[pos.r][pos.c] = true;

        const auto& curr_puyo = board.view(pos);
        stored_puyos.push_back(pos);
        
        if(curr_puyo.is_colored())
            ++color_puyo_count;
        weight_sum += curr_puyo.get_weight();

        for(const auto& dpos: DIR)
        {
            const auto& npos = pos+dpos;
            if (!board.in(npos))
                continue;
            const auto& npuyo = board.view(npos);
            if (curr_puyo.is_linkable(npuyo) && !visited[npos.r][npos.c])
                coords.push(npos);
        }
    }
    return make_tuple(color_puyo_count, weight_sum, stored_puyos);
}
tuple<int, vector<int>, vector<puyoType::Type>, vector<puyoPuyo>> puyoVanishControll::to_vanish_puyo(puyoBoard& board)
{
    int puyo_count = 0;
    vector<int> link_count;
    vector<puyoType::Type> color_count;
    vector<puyoPuyo> temp_energy_puyos;

    const auto& bsize = board.get_size();
    vector<vector<bool>> visited(bsize.r, vector<bool>(bsize.c, false));
    for (size_t i = 0; i < bsize.r; ++i)
        for (size_t j = 0; j < bsize.c; ++j)
        {
            if(visited[i][j])
                continue;
            
            const auto& curr_puyo = board.view({j, i});
            if(!curr_puyo.is_colored())
                continue;
            const auto& [color_puyo_count, weight_sum, stored_puyos] = fire_cluster(board,{j, i}, visited);
            if(weight_sum >= condition_for_vanish)
            {
                puyo_count += color_puyo_count;
                link_count.push_back(color_puyo_count);
                color_count.push_back(curr_puyo.get_type());
                for(const auto& pos : stored_puyos)
                {
                    auto vanish_puyo = board.to_vanish_puyo(pos);
                    temp_energy_puyos.push_back(vanish_puyo);
                    add(std::move(vanish_puyo));
                }
            }
    }
    return make_tuple(puyo_count, link_count, color_count, temp_energy_puyos);
}
void puyoVanishControll::set_condition(int amount){condition_for_vanish = amount;}
int puyoVanishControll::get_condition() const { return condition_for_vanish; }