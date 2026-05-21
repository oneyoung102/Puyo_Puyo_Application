#include "puyoBotModel1.hpp"
#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoPlayer/puyoPlayer.hpp"


#include <queue>
#include <vector>

using namespace std;


puyoBotModel1::puyoBotModel1(POSi bsize, unsigned int init_act_tick)
    : puyoBot(bsize, init_act_tick)
{}

void puyoBotModel1::think_perfect_lets(const puyoPlayer& player)
{
    const auto& board = player.get_board();
    const auto& puyo = player.get_puyo();

    int puyo_count = 0;
    const auto& bsize = board.get_size();
    for(size_t i = 0 ; i < bsize.r ; ++i)
        for(size_t j = 0 ; j < bsize.c ; ++j)
        {
            const auto& pos = POSs(j, i);
            if(simulate_board.get_puyo(pos) != board.get_puyo(pos))
                simulate_board.insert_puyo(board.get_puyo(pos));
            if(!simulate_board.empty(pos))
                ++puyo_count;
        }

    const bool fire_chain = get_fire(puyo_count,player.controll_obstuct().get());

    const auto& spawn_pos = board.get_spawn_pos();
    PROBABLITY perfect_probablity(-spawn_pos.x,0);
    int max_cluster_size = 0, max_cluster_size_sum = 0, bottom_y = 0;

    for(const auto& probablity : calc_all_probablities(board))
    {
        const auto& [temp_pos1,temp_pos2] = to_coord(probablity,puyo);
        if(!board.in(temp_pos1) || !board.in(temp_pos2))
            continue;
        auto [puyo1,puyo2] = puyo.get();
        puyo1.move(temp_pos1);
        puyo2.move(temp_pos2);
        
        const auto& [pos1,pos2] = simulate_drop({puyo1,puyo2});
        if(board.in(pos1) && board.in(pos2))
        {
            puyo1.move(pos1);
            puyo2.move(pos2);
            simulate_board.insert_puyo(puyo1);
            simulate_board.insert_puyo(puyo2);

            int cluster_size = 0, cluster_size_sum = 0;
            vector<vector<bool>> visited(bsize.r,vector<bool>(bsize.c,false));
            vector<puyoPuyo> changed;
            changed.push_back(puyo1);
            changed.push_back(puyo2);

            for(const auto& curr_puyo : changed)
            {
                int temp_cluster_size = 0;
                queue<POSi> coords;
                coords.push(curr_puyo.get_pos());
                while(!coords.empty())
                {
                    const auto& cpos = coords.front();
                    coords.pop();
                    if(visited[cpos.r][cpos.c])
                        continue;
                    visited[cpos.r][cpos.c] = true;
                    ++temp_cluster_size;
                    for(const auto& dpos : DIR)
                    {
                        const auto& npos = cpos+dpos;
                        if(!board.in(npos))
                            continue;
                        const auto& npuyo = simulate_board.get_puyo(npos);
                        if(npuyo == curr_puyo && !visited[npos.r][npos.c])
                            coords.push(npos);
                    }
                }
                cluster_size = max(cluster_size,temp_cluster_size);
                cluster_size_sum += temp_cluster_size;
            }
            
            const int temp_bottom_y = max(pos1.y,pos2.y);
            if(cluster_size < player.controll_vanish().get_condition()|| fire_chain)
                if(max_cluster_size < cluster_size
                || max_cluster_size == cluster_size && max_cluster_size_sum < cluster_size_sum
                || max_cluster_size == cluster_size && max_cluster_size_sum == cluster_size_sum &&  bottom_y < temp_bottom_y)
                {
                    max_cluster_size = cluster_size;
                    max_cluster_size_sum = cluster_size_sum;
                    perfect_probablity = probablity;
                    bottom_y = temp_bottom_y;
                }
            simulate_board.remove_puyo(pos1); //복구
            simulate_board.remove_puyo(pos2);
        }
    }
    to_let(perfect_probablity,const_cast<puyoPlayPuyo&>(puyo));
}