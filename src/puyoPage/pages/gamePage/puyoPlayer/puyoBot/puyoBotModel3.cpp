#include "puyoBotModel3.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include "puyoPage/pages/gamePage/puyoPlayer/puyoPlayer.hpp"
#include <climits>

using namespace std;


puyoBotModel3::puyoBotModel3(decltype(new_puyos)& new_types, const int& next_puyo_count, POSi bsize, unsigned int init_act_tick)
    : puyoBot(bsize,init_act_tick)
    , new_puyos(new_types)
    , next_puyo_count(next_puyo_count)
    , beam_search_select_count(3)
{}

int puyoBotModel3::simulate_chain(const puyoPlayer& player, POSi simul_drop_pos)
{
    const POSf bsize = simulate_board.get_size();
    puyoBoard board;
    for(size_t r = 0; r < bsize.r; ++r)
        for(size_t c = 0; c < bsize.c; ++c)
            board.insert(simulate_board.view({c, r}));
 
    int vanished_puyo = 0;
    bool continue_vanish = true;

    vector<vector<bool>> temp_visited(bsize.r, vector<bool>(bsize.c, false));
    const auto& [_1, _2, initial_stored] = player.controll_vanish().fire_cluster(board, simul_drop_pos, temp_visited);
    vanished_puyo += initial_stored.size();
    for(const auto& pos : initial_stored)
        board.remove(pos);
    
    while(continue_vanish)
    {
        for(size_t c = 0; c < bsize.c; ++c)
        {
            int write_idx = bsize.r-1;
            for(int read_idx = bsize.r-1; read_idx >= 0; --read_idx)
            {
                const auto pos = POSs(c, read_idx);
                if(!board.empty(pos))
                {
                    if(write_idx != read_idx)
                    {
                        board.insert(board.view(pos), POSs(c, write_idx));
                        board.remove(pos);
                    }
                    --write_idx;
                }
            }
        }
        continue_vanish = false;
        vector<vector<bool>> visited(bsize.r, vector<bool>(bsize.c, false));
        for(size_t r = 0; r < bsize.r; ++r)
            for(size_t c = 0; c < bsize.c; ++c)
            {
                const auto& puyo = board.view(POSs(c,r));
                if(puyo.empty() || visited[r][c] || !puyo.is_colored())
                    continue;

                const auto [color_puyo_count, weight_sum, stored_puyos] = player.controll_vanish().fire_cluster(board, POSs(c,r), visited);
                if(weight_sum >= player.controll_vanish().get_condition())
                { 
                    vanished_puyo += stored_puyos.size();
                    for(const auto& pos : stored_puyos)
                        board.remove(pos);
                    continue_vanish = true;
                }
            }
    }
    return vanished_puyo;
}

int puyoBotModel3::get_potential(const puyoPlayer& player, const std::vector<puyoPuyo>& deployed_puyos)
{
    const auto bsize = simulate_board.get_size();
    int max_potential = 0;

    for(size_t c = 0; c < bsize.c; ++c)
    {
        POSs pos = {c,0};
        while(pos.r < bsize.r && simulate_board.empty(pos))
            ++pos.r;
        if(pos.r == bsize.r || !simulate_board.view(pos).is_colored())
            continue;

        const auto vanish_count = simulate_chain(player, pos);
        max_potential = max(max_potential, vanish_count);
    } 
    for(const auto& puyo : deployed_puyos)
    {
        const auto& pos = puyo.get_pos();
        if(simulate_board.in_row(pos.r-1) && !simulate_board.empty(pos+POSi(0,-1)))// 위가 가려진 플레이뿌요 터뜨림
        {
            const auto vanish_count = simulate_chain(player, pos);
            max_potential = max(max_potential, vanish_count);
        }
    }
    return max_potential;
}

bool puyoBotModel3::fire_able(const puyoPlayer& player, const std::vector<puyoPuyo>& deployed_puyos)
{
    const auto& bsize = simulate_board.get_size();
    const int R = bsize.r, C = bsize.c;
    vector<vector<bool>> visited(R,vector<bool>(C,false));
    int max_cluster_size = 0; 
    for(const auto& puyo : deployed_puyos)
    {
        const auto&[cluster_size, _1,_2] = player.controll_vanish().fire_cluster(simulate_board, puyo.get_pos(), visited);
        max_cluster_size = max(max_cluster_size,cluster_size);   
    }
    return max_cluster_size >= player.controll_vanish().get_condition();
}

pair<int,puyoBotModel3::PROBABLITY> puyoBotModel3::beam_search(const puyoPlayer& player, const puyoBoard& board, const vector<pair<puyoPuyo,puyoPuyo>>& next_types, int count, const bool fire)
{
    const bool first_turn = count == 0, last_turn = count == puyoGameConstant::DISPLAYED_NEXT_PUYO_COUNT;

    PROBABLITY best_probablity;
    int max_potential = INT_MIN;
    using PROB_TYPE = tuple<int,PROBABLITY,vector<puyoPuyo>>; // {potential, probablity, puyoPuyo...}
    vector<PROB_TYPE> best_probablities;

    for(const auto& probablity : calc_all_probablities(board))
    {
        const auto& [temp_pos1,temp_pos2] = to_coord(probablity,player.refer_puyo());
        if(!board.in(temp_pos1) || !board.in(temp_pos2))
            continue;
        auto [puyo1,puyo2] = next_types[count];
        puyo1.move(temp_pos1);
        puyo2.move(temp_pos2);
        const auto& [pos1,pos2] = simulate_drop({puyo1,puyo2});
        if(!board.in(pos1) || !board.in(pos2))
            continue;
        puyo1.move(pos1);
        puyo2.move(pos2);
        simulate_board.insert(puyo1);
        simulate_board.insert(puyo2);

        int potential = 0;
        if(first_turn)
        {
            const bool fire_able = this->fire_able(player,{puyo1,puyo2});
            if(fire && !fire_able || !fire && fire_able)
                potential += puyoGameConstant::BOT_PENALTY;
        }
        potential += get_potential(player,{puyo1,puyo2});
        if(last_turn)
        {
            if(potential > max_potential)
            {
                max_potential = potential;
                best_probablity = probablity;
            }
        }
        else
            best_probablities.push_back({potential, probablity, {puyo1,puyo2}});

        simulate_board.remove(pos1);//복구
        simulate_board.remove(pos2);
    }

    if(last_turn)
        return {max_potential, best_probablity};

    sort(best_probablities.begin(),best_probablities.end(),[](const PROB_TYPE& x, const PROB_TYPE& y){
        return get<0>(x) > get<0>(y);
    });
    if(best_probablities.size() > beam_search_select_count) 
        best_probablities.resize(beam_search_select_count);
    for(auto& probablity : best_probablities)
    {
        for(const auto& puyo : get<2>(probablity))
            simulate_board.insert(puyo);

        get<0>(probablity) += beam_search(player,simulate_board,next_types,count+1,fire).first;

        for(const auto& puyo : get<2>(probablity))
            simulate_board.remove(puyo.get_pos());
    }

    const auto& best_of_best = *max_element(best_probablities.begin(),best_probablities.end(),[](const PROB_TYPE& x, const PROB_TYPE& y){
        return get<0>(x) < get<0>(y);
    });
    return make_pair(get<0>(best_of_best),get<1>(best_of_best));
}

void puyoBotModel3::think_perfect_lets(const puyoPlayer& player)
{
    const auto& board = player.refer_board();
    const auto& puyo = player.refer_puyo();

    const auto& bsize = board.get_size();
    
    int all_puyo_sum = 0;
    for(size_t i = 0 ; i < bsize.r ; ++i)
        for(size_t j = 0 ; j < bsize.c ; ++j)
        {
            const auto& pos = POSs(j, i);
            if(simulate_board.view(pos) != board.view(pos))
                simulate_board.insert(board.view(pos));
            if(!simulate_board.empty(pos))
                ++all_puyo_sum;
        }
    if(new_puyos.empty())
        return;
    const bool fire = get_fire(all_puyo_sum,player.controll_obstuct().get());
    const PROBABLITY& best_probablity = beam_search(player,board,
        {puyo.view(),new_puyos.view(next_puyo_count),new_puyos.view(next_puyo_count+1)}
        ,0,fire).second;
    to_let(best_probablity,const_cast<puyoPlayPuyo&>(puyo));
}