#include "puyoBotModel2.hpp"
#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoPlayer/puyoBot/puyoBot.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType.hpp"
#include "puyoResources/puyoFileSystem.hpp"

#include <climits>
#include <iostream>
#include <queue>
#include <vector>
#include <cmath>

#include <fstream>

using namespace std;


void puyoBotModel2::saveModel(const string& filename) {
    std::ofstream ofs(filename);
    if (!ofs.is_open()) 
        return;
    for (size_t j = 0; j < COUNT; ++j)
        ofs << weights[j] << " ";
    ofs << "\n";
    ofs << N_count << "\n";
    for (int i = 0; i < COUNT; ++i)
        ofs << parameters_mean[i] << " ";
    ofs << "\n";
    for (int i = 0; i < COUNT; ++i)
        ofs << parameters_stdev[i] << " ";
    ofs << "\n";
    ofs << expected_mean_scores.size() << "\n";
    for (auto val : expected_mean_scores)
        ofs << val << " ";
    ofs << "\n";
    for (auto val : expected_mean_count)
        ofs << val << " ";
    ofs << "\n";

    ofs.close();
    std::cout << "Model saved to " << filename << std::endl;
}

void puyoBotModel2::loadModel(const std::string& filename) {
    std::ifstream ifs(filename);
    if (!ifs.is_open()) {
        std::cout << "No saved model found. Starting with default values." << std::endl;
        return;
    }
    for (size_t j = 0; j < COUNT; ++j)
        ifs >> weights[j];
    ifs >> N_count;
    for (int i = 0; i < COUNT; ++i)
        ifs >> parameters_mean[i];
    for (int i = 0; i < COUNT; ++i)
        ifs >> parameters_stdev[i];
    size_t size;
    ifs >> size;
    expected_mean_scores.resize(size);
    expected_mean_count.resize(size);
    for (size_t i = 0; i < size; ++i)
        ifs >> expected_mean_scores[i];
    for (size_t i = 0; i < size; ++i)
        ifs >> expected_mean_count[i];

    ifs.close();
}

puyoBotModel2::puyoBotModel2(const int& curr_score, POSi bsize, unsigned int init_act_tick)
    : puyoBot(bsize,init_act_tick)
    , STAIR_DIR({DIR[LEFT]+DIR[UP], DIR[LEFT]+DIR[DOWN], DIR[RIGHT]+DIR[UP], DIR[RIGHT]+DIR[DOWN]})
    , MIN_VALUE(1e-10)
    , signs({1,1,-1,1,1,-1,-1})
    , curr_score(curr_score)
    , prev_score(curr_score)
    , prev_color_puyo_sum(0)
{
    weights.fill(1.0/COUNT);
    parameters_sum.fill(0);
    N_count = 0;
    parameters_mean.fill(0);
    parameters_stdev.fill(0.1);
    expected_mean_scores = vector<PARAM_TYPE>(bsize.r*bsize.c+1,0);
    expected_mean_count = vector<int>(bsize.r*bsize.c+1,0);

    loadModel(puyoFileSystem::getFolderPath("Data")/"puyoBotModel2Data.txt");
}
puyoBotModel2::~puyoBotModel2()
{
    saveModel(puyoFileSystem::getFolderPath("Data")/"puyoBotModel2Data.txt");
}

puyoBotModel2::PARAM_TYPE puyoBotModel2::get_ratio(ParameterName name, PARAM_TYPE x)
{
    const PARAM_TYPE z = (x - parameters_mean[name]) / parameters_stdev[name];
    const PARAM_TYPE norm_value = (1.0 + erf(z * M_SQRT1_2))/2.0;
    return (signs[name] > 0) ? norm_value : (1.0 - norm_value);
}
puyoBotModel2::PARAM_TYPE puyoBotModel2::get_new_stdev(ParameterName name, PARAM_TYPE old_mean, PARAM_TYPE x)
{
    if (N_count <= 1) return 0.1; 
    const PARAM_TYPE new_mean = parameters_mean[name];
    const PARAM_TYPE old_stdev = parameters_stdev[name];
    const PARAM_TYPE old_var = old_stdev * old_stdev;
    const PARAM_TYPE new_var = old_var + ((x - old_mean) * (x - new_mean) - old_var) / N_count;
    return sqrt(fmax(new_var, MIN_VALUE));
}
puyoBotModel2::PARAM_TYPE puyoBotModel2::get_bias()
{
    uniform_int_distribution<> bias(-1,1); // 편향
    return bias(gen)/2.0;
}



pair<puyoBotModel2::PARAM_TYPE,puyoBotModel2::PARAM_TYPE> puyoBotModel2::get_cluster_sizes(const vector<pair<POSi,puyoType>>& deployed_puyos)
{
    const auto bsize = simulate_board.get_size();
    const int R = bsize.r, C = bsize.c;
    vector<vector<bool>> visited(R,vector<bool>(C,false));

    int max_cluster_size = 0, cluster_size_sum = 0;
    for(const auto[pos,type] : deployed_puyos)
    {
        int cluster_size = 0;
        queue<POSi> coords;
        coords.push(pos);
        while(!coords.empty())
        {
            const auto cpos = coords.front();
            coords.pop();
            if(visited[cpos.r][cpos.c])
                continue;
            visited[cpos.r][cpos.c] = true;
            ++cluster_size;
            for(const auto dpos : DIR)
            {
                const auto npos = cpos+dpos;
                if(npos.r < 0 || npos.r >= R || npos.c < 0 || npos.c >= C)
                    continue;
                const puyoType npuyo = simulate_board.get_puyo(POSs(npos.c, npos.r));
                if(npuyo == type && !visited[npos.r][npos.c])
                    coords.push(npos);
            }
        }
        max_cluster_size = max(max_cluster_size,cluster_size);
        cluster_size_sum += cluster_size;
    }
    return {max_cluster_size,cluster_size_sum};
}
puyoBotModel2::PARAM_TYPE puyoBotModel2::get_column_diversity(const vector<POSi>& deployed_puyos)
{
    PARAM_TYPE diversity = 0;
    for(const auto pos : deployed_puyos)
    {
        PARAM_TYPE temp_diversity = 0;
        int count = 0;
        for(int r = simulate_board.get_size().r - 1 ; r > 0  ; --r)
        {
            ++count;
            const auto type = simulate_board.get_puyo(POSs(pos.c, r-1));
            if(type == puyoType::blank)
                break;
            if(simulate_board.get_puyo(POSs(pos.c, r)) != type)
                ++temp_diversity;
        }      
        diversity += temp_diversity/count; 
    }
    return diversity; // 두 뿌요의 열 다양성 평균
}
puyoBotModel2::PARAM_TYPE puyoBotModel2::get_row_height(const vector<POSi>& deployed_puyos)
{
    int row_height_sum = 2; // 두 뿌요가 배치됨으로써 높이가 2 높아짐
    const auto bsize = simulate_board.get_size();
    const int R = bsize.r, C = bsize.c;
    for(size_t c = 0 ; c < C ; ++c)
        for(size_t r = 0 ; r <= R ; ++r)
            if(r == R || simulate_board.get_puyo(POSs(c, r)) != puyoType::blank)
            {
                row_height_sum += r;
                break;
            }
    return (deployed_puyos[0].r+deployed_puyos[1].r)/CASTf(row_height_sum);
}
puyoBotModel2::PARAM_TYPE puyoBotModel2::get_stair_level(const vector<pair<POSi,puyoType>>& deployed_puyos)
{
    const auto bsize = simulate_board.get_size();
    const int R = bsize.r, C = bsize.c;
    PARAM_TYPE stair_level = 0.0;
    for(const auto[pos,type] : deployed_puyos)
        for(const auto& dpos : STAIR_DIR)
        {
            const auto npos = pos+dpos;
            if(npos.r < 0 || npos.r >= R || npos.c < 0 || npos.c >= C)
                continue;
            if(simulate_board.get_puyo(POSs(npos.c, npos.r)) == type)
                ++stair_level;
        }
    return stair_level;
}
puyoBotModel2::PARAM_TYPE puyoBotModel2::get_flatness(const vector<POSi>& deployed_puyos)
{
    const auto bsize = simulate_board.get_size();
    const int R = bsize.r, C = bsize.c;
    PARAM_TYPE flatness = 0.0;
    for(const auto pos : deployed_puyos)
    {
        int count = 2; // LEFT,RIGHT 두 방향
        PARAM_TYPE several_flatness = 0.0;
        for(const auto& dpos : decltype(DIR)({DIR[LEFT],DIR[RIGHT]}))
        {
            const auto c = pos.c+dpos.c;
            if(0 > c || c >= C)
            {
                --count;
                continue;
            }
            for(size_t r = 0 ; r <= R ; ++r)
                if(r == R || simulate_board.get_puyo(POSs(c, r)) != puyoType::blank)
                {
                    several_flatness += fabs(static_cast<PARAM_TYPE>(r)-pos.r);
                    break;
                }
        }
        flatness += several_flatness/count; // count != 0
    }
    return flatness;
}
puyoBotModel2::PARAM_TYPE puyoBotModel2::get_isolated(const vector<pair<POSi,puyoType>>& deployed_puyos)
{
    const auto bsize = simulate_board.get_size();
    const int R = bsize.r, C = bsize.c;
    PARAM_TYPE isolated = 0.0;
    for(const auto[pos,type] : deployed_puyos)
    {
        PARAM_TYPE temp_isolated = 0.0;
        int count = DIR.size();
        for(const auto& dpos : DIR)
        {
            const auto npos = pos+dpos;
            if(npos.r < 0 || npos.r >= R || npos.c < 0 || npos.c >= C)
            {
                ++temp_isolated;
                continue;
            }
            if(simulate_board.get_puyo(POSs(npos.c, npos.r)) == puyoType::blank)
                --count;
            else if(simulate_board.get_puyo(POSs(npos.c, npos.r)) != type)
                ++temp_isolated;
        }
            isolated += temp_isolated/count;
    }
    return isolated;
}

puyoBotModel2::PARAM_TYPE puyoBotModel2::get_expected_mean_score(int color_puyo_sum, int dscore)
{
    if(color_puyo_sum < 0)
        throw("color_puyo_sum is smaller than 0");

    const int MODIFIED_SCORE = expected_mean_scores[color_puyo_sum];
    for(int i = color_puyo_sum ; i < expected_mean_scores.size() ; ++i)
    {
        const int PREV_SCORE = expected_mean_scores[i], PREV_COUNT = expected_mean_count[i];
        expected_mean_scores[i] = fmax(expected_mean_scores[max(i-1,0)],(PREV_SCORE*PREV_COUNT+dscore)/(PREV_COUNT+1));
        expected_mean_count[i] = min(PREV_COUNT+1,INT_MAX);
    }
    return MODIFIED_SCORE;
}

puyoBotModel2::PARAM_TYPE puyoBotModel2::sigmoid(PARAM_TYPE score, PARAM_TYPE expected_min_score)
{
    if(expected_min_score == 0)
        return 0.5;
    return 1.0/(1+exp(-(score-expected_min_score)/expected_min_score));
}
puyoBotModel2::PARAM_TYPE puyoBotModel2::is_activated(PARAM_TYPE value){return value-0.5;}
void puyoBotModel2::backpropagation(int color_puyo_sum)
{
    const int dscore = curr_score-prev_score;
    if(dscore <= simulate_board.get_size().r) // 낙하 점수 보너스로 얻는 점수 변화량 무시
    {
        prev_score = curr_score;
        return;
    }

    // for(size_t i = 0 ; i < COUNT ; ++i)
    //     std::cout << weights[i] << " ";
    // std::cout << std::endl;

    const PARAM_TYPE expected_mean_dscore = get_expected_mean_score(color_puyo_sum,dscore);
    const PARAM_TYPE SCORE_VALUE = sigmoid(dscore,expected_mean_dscore); // 시그모이드 함수
    const PARAM_TYPE DELTA = (1.0/(COUNT*sqrt(N_count+1.0)))*is_activated(SCORE_VALUE);

    PARAM_TYPE parameters_sum_total = 0.0;
    for(size_t i = 0 ; i < COUNT ; ++i)
        parameters_sum_total += parameters_sum[i];
    parameters_sum_total = max(parameters_sum_total,MIN_VALUE);

    PARAM_TYPE weight_sum = 0.0;
    for(size_t i = 0 ; i < COUNT ; ++i)
    {
        const PARAM_TYPE DVALUE = DELTA*parameters_sum[i]/parameters_sum_total;
        weights[i] += DVALUE; 
        weights[i] = fmax(weights[i], 0.02); 
        weight_sum += weights[i];
    }
    weight_sum = max(weight_sum,MIN_VALUE);

    for(size_t i = 0 ; i < COUNT ; ++i)
        weights[i] /= weight_sum;
    parameters_sum.fill(0);
    prev_score = curr_score;
}

int puyoBotModel2::simulate_chain(POSi simul_drop_pos, int vanish_condition)
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
                if(type == puyoType::blank || visited[r][c] || !is_colored(type))
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

int puyoBotModel2::get_potential(int vanish_condition)
{
    const auto bsize = simulate_board.get_size();
    int max_potential = 0;

    for(size_t c = 0; c < bsize.c; ++c)
    {
        size_t drop_r = 0;
        while(drop_r < bsize.r && simulate_board.empty(POSs(c, drop_r)))
            ++drop_r;
        if(drop_r == bsize.r || !is_colored(simulate_board.get_puyo(POSs(c, drop_r))))
            continue;

        const auto vanish_count = simulate_chain(POSi(c,drop_r), vanish_condition);
        max_potential = max(max_potential, vanish_count);
    } 
    return max_potential;
}

void puyoBotModel2::think_perfect_lets(const puyoBoard& board, const puyoPlayPuyo& puyo)
{
    N_count = min(N_count+1,INT_MAX);
    backpropagation(prev_color_puyo_sum);

    const auto bsize = board.get_size();
    const auto condition = board.controll_vanish().get_condition();

    int all_puyo_sum = 0, color_puyo_sum = 0;
    for(size_t i = 0 ; i < bsize.r ; ++i)
        for(size_t j = 0 ; j < bsize.c ; ++j)
        {
            const auto pos = POSs(j, i);
            simulate_board.insert_puyo(board.get_puyo(pos), pos);
            if(!simulate_board.empty(pos))
            {
                ++all_puyo_sum;
                if(is_colored(simulate_board.get_puyo(pos)))
                    ++color_puyo_sum;
            }
        }
    prev_color_puyo_sum = color_puyo_sum;

    const auto spawn_pos = board.get_spawn_pos();
    PROBABLITY best_probablity_fire(-spawn_pos.x,0), best_probablity_buildup(-spawn_pos.x,0);
    int max_potential = 0;
    PARAM_TYPE max_z_value = -numeric_limits<PARAM_TYPE>::infinity();
    std::array<PARAM_TYPE, COUNT> best_parameters; best_parameters.fill(0);

    const bool fire_ask = get_fire(all_puyo_sum,board.controll_obstuct().get());
    bool fire_able = false;

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

            array<PARAM_TYPE, COUNT> current_parameters;
            PARAM_TYPE z_value = 0.0;

            const auto [max_cluster_size, cluster_size_sum] = get_cluster_sizes({{pos1,type1},{pos2,type2}});
            current_parameters[ParameterName::max_cluster_size] = max_cluster_size;
            current_parameters[ParameterName::cluster_size_sum] = cluster_size_sum;
            current_parameters[ParameterName::column_diversity] = get_column_diversity({pos1,pos2});
            current_parameters[ParameterName::row_height] = get_row_height({pos1,pos2});
            current_parameters[ParameterName::stair_level] = get_stair_level({{pos1,type1},{pos2,type2}});
            current_parameters[ParameterName::flatness] = get_flatness({pos1,pos2});
            current_parameters[ParameterName::isolated] = get_isolated({{pos1,type1},{pos2,type2}});   
            for(size_t i = 0 ; i < COUNT ; ++i)
            {
                const auto NAME = static_cast<ParameterName>(i);
                const PARAM_TYPE ratio = get_ratio(NAME, current_parameters[NAME]);
                z_value += weights[NAME]*ratio;
            }
            if(max_cluster_size >= condition)
                z_value -= 100000; //페널티
            if(z_value > max_z_value)
            {
                max_z_value = z_value;
                best_probablity_buildup = probablity;
                best_parameters = current_parameters; 
            }

            const int potential = get_potential(condition);
            if(potential > max_potential)
                if(!fire_ask || max_cluster_size >= condition)
                {
                    max_potential = potential;
                    best_probablity_fire = probablity;
                    fire_able = max_cluster_size >= condition;
                }  

            simulate_board.remove_puyo(pos1);//복구
            simulate_board.remove_puyo(pos2);
        }
    }
    for(size_t i = 0 ; i < COUNT ; ++i)
    {
        const auto NAME = static_cast<ParameterName>(i);
        const PARAM_TYPE old_mean = parameters_mean[i];
        
        parameters_mean[i] = (parameters_mean[i] * (N_count - 1) + best_parameters[i]) / N_count;
        parameters_stdev[i] = get_new_stdev(NAME, old_mean, best_parameters[i]);
        parameters_sum[i] += get_ratio(NAME, best_parameters[i]);
    }
    const bool all_clear = max_potential == all_puyo_sum+2;
    if(all_clear || fire_able && fire_ask || !fire_able && max_potential >= condition)
        to_let(best_probablity_fire,const_cast<puyoPlayPuyo&>(puyo));
    else
        to_let(best_probablity_buildup,const_cast<puyoPlayPuyo&>(puyo));
}