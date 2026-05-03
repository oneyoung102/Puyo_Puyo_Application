#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoBoardControll/puyoBoardVanishControll.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoAction/puyoPuyoVanish.hpp"
#include <queue>
#include <utility>

#include "puyoTool/puyoDir.hpp"

using namespace std;

puyoBoardVanishControll::puyoBoardVanishControll(){}

void puyoBoardVanishControll::add(PUYO_INFO puyo)
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

void puyoBoardVanishControll::to_vanish_puyo_each(puyoBoard& board, const PUYO_INFO& puyo)
{
    const auto[pos,type,tick] = puyo;
    add(puyo);
    board.controll_energy().add_temp({pos, type, puyoGameConstant::BOARD_FLY_TICK});
    board.remove_puyo(pos);
}
pair<int,vector<pair<POSs, puyoType>>> puyoBoardVanishControll::fire_cluster(const puyoBoard& board, POSs fire_pos, vector<vector<bool>>& visited)
{
    int other_puyos = 0;
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
        
        if(curr_puyo == puyoType::obstruct)
        {
            ++other_puyos;
            continue;
        }
        for (const auto dpos: DIR)
        {
            const auto npos = pos+dpos;
            if (!board.in(npos))
                continue;
            const puyoType npuyo = board.get_puyo(npos);
            if ((npuyo == puyo || npuyo == puyoType::obstruct) && !visited[npos.r][npos.c])
                coords.push(npos);
        }
    }
    return make_pair(stored_puyos.size() - other_puyos, stored_puyos);
}
tuple<int, vector<int>, vector<puyoType>> puyoBoardVanishControll::to_vanish_puyo(puyoBoard& board)
{
   int puyo_count = 0;
   vector<int> link_count;
   vector<puyoType> color_count;
    const auto bsize = board.get_size();
    vector<vector<bool>> visited(bsize.r, vector<bool>(bsize.c, false));
    for (size_t i = 0; i < bsize.r; ++i)
        for (size_t j = 0; j < bsize.c; ++j)
        {
            if(visited[i][j])
                continue;
            const puyoType puyo = board.get_puyo({j, i});
            if(!is_colored(puyo))
                continue;
            auto [color_puyo_count, stored_puyos] = fire_cluster(board,{j, i}, visited);
            if(color_puyo_count >= condition_for_vanish)
            {
                puyo_count += color_puyo_count;
                link_count.push_back(color_puyo_count);
                color_count.push_back(puyo);
                for(const auto [pos, type] : stored_puyos)
                {
                    const int tick = (type == puyoType::obstruct) ? puyoGameConstant::BOARD_OBSTRUCT_VANISH_TICK : puyoGameConstant::BOARD_BASIC_VANISH_TICK;
                    to_vanish_puyo_each(board,{pos,type,tick});
                }
            }
    }
    return make_tuple(puyo_count, link_count, color_count);
}
void puyoBoardVanishControll::set_condition(int amount){condition_for_vanish = amount;}
int puyoBoardVanishControll::get_condition() const { return condition_for_vanish; }