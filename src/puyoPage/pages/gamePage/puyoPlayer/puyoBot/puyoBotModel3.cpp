#include "puyoBotModel3.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoPlayer/puyoBot/puyoBot.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/puyoType.hpp"
#include <climits>

using namespace std;


puyoBotModel3::puyoBotModel3(const std::vector<std::pair<puyoType,puyoType>>& new_types, const int& next_puyo_count, POSi bsize, unsigned int init_act_tick)
    : puyoBot(bsize,init_act_tick)
    , new_types(new_types)
    , next_puyo_count(next_puyo_count)
    , beam_search_select_count(3)
{}

int puyoBotModel3::simulate_chain(POSi simul_drop_pos, int vanish_condition)
{
    const POSf bsize = simulate_board.get_size();
    puyoBoard board;
    for(int r = 0; r < bsize.r; ++r)
        for(int c = 0; c < bsize.c; ++c)
            board.insert_puyo(simulate_board.get_puyo(POSs(c, r)), POSs(c, r));
 
    int vanished_puyo = 0;
    bool continue_vanish = true;

    vector<vector<bool>> temp_visited(bsize.r, vector<bool>(bsize.c, false));
    const auto [_, initial_stored] = board.controll_vanish().fire_cluster(board, simul_drop_pos, temp_visited);
    vanished_puyo += initial_stored.size();
    for(const auto& p : initial_stored)
        board.remove_puyo(p.first);
    
    while(continue_vanish)
    {
        for(int c = 0; c < bsize.c; ++c)
        {
            int write_idx = bsize.r-1;
            for(int read_idx = bsize.r-1; read_idx >= 0; --read_idx)
                if(!board.empty(POSs(c, read_idx)))
                {
                    if(write_idx != read_idx)
                    {
                        board.insert_puyo(board.get_puyo(POSs(c,read_idx)), POSs(c, write_idx));
                        board.remove_puyo(POSs(c, read_idx));
                    }
                    --write_idx;
                }
        }
        continue_vanish = false;
        vector<vector<bool>> visited(bsize.r, vector<bool>(bsize.c, false));
        for(size_t r = 0; r < bsize.r; ++r)
            for(size_t c = 0; c < bsize.c; ++c)
            {
                const puyoType type = board.get_puyo(POSs(c,r));
                if(type.empty() || visited[r][c] || !type.is_colored())
                    continue;

                const auto [color_puyo_count, stored_puyos] = board.controll_vanish().fire_cluster(board, POSs(c,r), visited);
                if(color_puyo_count >= vanish_condition)
                { 
                    vanished_puyo += stored_puyos.size();
                    for(const auto& p : stored_puyos)
                        board.remove_puyo(p.first);
                    continue_vanish = true;
                }
            }
    }
    return vanished_puyo;
}

int puyoBotModel3::get_potential(int vanish_condition, const std::vector<POSi>& deployed_puyos)
{
    const auto bsize = simulate_board.get_size();
    int max_potential = 0;

    for(size_t c = 0; c < bsize.c; ++c)
    {
        size_t drop_r = 0;
        while(drop_r < bsize.r && simulate_board.empty(POSs(c, drop_r)))
            ++drop_r;
        if(drop_r == bsize.r || !simulate_board.get_puyo(POSs(c, drop_r)).is_colored())
            continue;

        const auto vanish_count = simulate_chain(POSi(c,drop_r), vanish_condition);
        max_potential = max(max_potential, vanish_count);
    } 
    for(const auto& pos : deployed_puyos)
        if(simulate_board.in_row(pos.r-1) && !simulate_board.empty(pos+POSi(0,-1)))// 위가 가려진 플레이뿌요 터뜨림
        {
            const auto vanish_count = simulate_chain(pos, vanish_condition);
            max_potential = max(max_potential, vanish_count);
        }
    return max_potential;
}

bool puyoBotModel3::fire_able(int vanish_condition, const std::vector<POSi>& deployed_puyos)
{
    const auto bsize = simulate_board.get_size();
    const int R = bsize.r, C = bsize.c;
    vector<vector<bool>> visited(R,vector<bool>(C,false));
    int max_cluster_size = 0; 
    for(const auto pos : deployed_puyos)
    {
        const auto[cluster_size, _] = simulate_board.controll_vanish().fire_cluster(simulate_board, pos, visited);
        max_cluster_size = max(max_cluster_size,cluster_size);   
    }
    return max_cluster_size >= vanish_condition;
}

pair<int,puyoBotModel3::PROBABLITY> puyoBotModel3::beam_search(const puyoBoard& board, const puyoPlayPuyo& puyo, const vector<pair<puyoType,puyoType>>& next_types, int count, const bool fire)
{
    const auto condition = board.controll_vanish().get_condition();
    const bool first_turn = count == 0, last_turn = count == puyoGameConstant::NEXT_PUYO_COUNT_DISPLAY;

    PROBABLITY best_probablity;
    int max_potential = INT_MIN;
    using PROB_TYPE = tuple<int,PROBABLITY,vector<pair<POSi,puyoType>>>; // {potential, probablity, {{pos,type}...}}
    vector<PROB_TYPE> best_probablities;

    for(const auto probablity : calc_all_probablities(board))
    {
        const auto[temp_pos1,temp_pos2] = to_coord(probablity,puyo);
        if(!board.in(temp_pos1) || !board.in(temp_pos2))
            continue;
        const auto [type1,type2] = next_types[count];
        const auto [pos1,pos2] = simulate_drop({{temp_pos1,type1},{temp_pos2,type2}});
        if(!board.in(pos1) || !board.in(pos2))
            continue;

        simulate_board.insert_puyo(type1, pos1);
        simulate_board.insert_puyo(type2, pos2);

        int potential = 0;
        if(first_turn)
        {
            const bool fire_able = this->fire_able(condition, {pos1,pos2});
            if(fire && !fire_able || !fire && fire_able)
                potential -= 10000;
        }
        potential += get_potential(condition,{pos1,pos2});
        if(last_turn)
        {
            if(potential > max_potential)
            {
                max_potential = potential;
                best_probablity = probablity;
            }
        }
        else
            best_probablities.push_back({potential, probablity, {{pos1,type1},{pos2,type2}}});

        simulate_board.remove_puyo(pos1);//복구
        simulate_board.remove_puyo(pos2);
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
        for(const auto& [pos,type] : get<2>(probablity))
            simulate_board.insert_puyo(type, pos);

        get<0>(probablity) += beam_search(simulate_board,puyo,next_types,count+1,fire).first;

        for(const auto& [pos,type] : get<2>(probablity))
            simulate_board.remove_puyo(pos);
    }

    const auto& best_of_best = *max_element(best_probablities.begin(),best_probablities.end(),[](const PROB_TYPE& x, const PROB_TYPE& y){
        return get<0>(x) < get<0>(y);
    });
    return make_pair(get<0>(best_of_best),get<1>(best_of_best));
}

void puyoBotModel3::think_perfect_lets(const puyoBoard& board, const puyoPlayPuyo& puyo)
{
    const auto bsize = board.get_size();
    
    int all_puyo_sum = 0;
    for(size_t i = 0 ; i < bsize.r ; ++i)
        for(size_t j = 0 ; j < bsize.c ; ++j)
        {
            const auto pos = POSs(j, i);
            simulate_board.insert_puyo(board.get_puyo(pos), pos);
            if(!simulate_board.empty(pos))
                ++all_puyo_sum;
        }
    if(new_types.empty())
        return;
    const bool fire = get_fire(all_puyo_sum,board.controll_obstuct().get());
    decltype(new_types) next_types = {puyo.get_type(),new_types[next_puyo_count],new_types[next_puyo_count+1]};
    const PROBABLITY best_probablity = beam_search(board,puyo,next_types,0,fire).second;
    to_let(best_probablity,const_cast<puyoPlayPuyo&>(puyo));
}