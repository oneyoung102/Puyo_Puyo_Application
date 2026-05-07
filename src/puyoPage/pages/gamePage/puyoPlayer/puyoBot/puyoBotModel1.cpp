#include "puyoBotModel1.hpp"
#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"

#include <queue>
#include <vector>

using namespace std;


puyoBotModel1::puyoBotModel1(POSi bsize, unsigned int init_act_tick)
    : puyoBot(bsize, init_act_tick)
{}

void puyoBotModel1::think_perfect_lets(const puyoBoard& board, const puyoPlayPuyo& puyo)
{
    int puyo_count = 0;
    const auto bsize = board.get_size();
    for(size_t i = 0 ; i < bsize.r ; ++i)
        for(size_t j = 0 ; j < bsize.c ; ++j)
        {
            simulate_board.insert_puyo(board.get_puyo({j, i}), POSs(j, i));
            if(!simulate_board.empty(POSs(j, i)))
                ++puyo_count;
        }

    const bool fire_chain = get_fire(puyo_count,board.controll_obstuct().get());

    const auto spawn_pos = board.get_spawn_pos();
    PROBABLITY perfect_probablity(-spawn_pos.x,0);
    int max_cluster_size = 0, max_cluster_size_sum = 0, bottom_y = 0;

    for(const auto probablity : calc_all_probablities(board))
    {
        const auto[temp_pos1,temp_pos2] = to_coord(probablity,puyo);
        if(!board.in(temp_pos1) || !board.in(temp_pos2))
            continue;
        const auto [type1,type2] = puyo.get_type();
        const auto [pos1,pos2] = simulate_drop({{temp_pos1,type1},{temp_pos2,type2}});
        if(board.in(pos1) && board.in(pos2))
        {
            simulate_board.insert_puyo(type1, pos1);
            simulate_board.insert_puyo(type2, pos2);

            int cluster_size = 0, cluster_size_sum = 0;
            vector<vector<bool>> visited(bsize.r,vector<bool>(bsize.c,false));
            vector<pair<POSi,puyoType>> changed;
            changed.push_back({pos1,type1});
            changed.push_back({pos2,type2});

            for(const auto[pos,curr_puyo] : changed)
            {
                int temp_cluster_size = 0;
                queue<POSi> coords;
                coords.push(pos);
                while(!coords.empty())
                {
                    const auto cpos = coords.front();
                    coords.pop();
                    if(visited[cpos.r][cpos.c])
                        continue;
                    visited[cpos.r][cpos.c] = true;
                    ++temp_cluster_size;
                    for(const auto dpos : DIR)
                    {
                        const auto npos = cpos+dpos;
                        if(!board.in(npos))
                            continue;
                        const puyoType npuyo = simulate_board.get_puyo(POSs(npos.c, npos.r));
                        if(npuyo == curr_puyo && !visited[npos.r][npos.c])
                            coords.push(npos);
                    }
                }
                cluster_size = max(cluster_size,temp_cluster_size);
                cluster_size_sum += temp_cluster_size;
            }
            
            const int temp_bottom_y = max(pos1.y,pos2.y);
            if(cluster_size < board.controll_vanish().get_condition()|| fire_chain)
                if(max_cluster_size < cluster_size
                || max_cluster_size == cluster_size && max_cluster_size_sum < cluster_size_sum
                || max_cluster_size == cluster_size && max_cluster_size_sum == cluster_size_sum &&  bottom_y < temp_bottom_y)
                {
                    max_cluster_size = cluster_size;
                    max_cluster_size_sum = cluster_size_sum;
                    perfect_probablity = probablity;
                    bottom_y = temp_bottom_y;
                }
        }
        simulate_board.remove_puyo(pos1); //복구
        simulate_board.remove_puyo(pos2);
    }
    to_let(perfect_probablity,const_cast<puyoPlayPuyo&>(puyo));
}