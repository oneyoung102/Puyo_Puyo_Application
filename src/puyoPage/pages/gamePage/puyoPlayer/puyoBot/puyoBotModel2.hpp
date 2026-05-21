#pragma once

#include "puyoPage/pages/gamePage/puyoPlayer/puyoBot/puyoBot.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/puyoType.hpp"
#include "puyoTool/puyoPos.hpp"
#include <vector>
#include <utility>
#include <array>
#include <string>

class puyoBotModel2 : public puyoBot
{
    private :
        enum ParameterName {
            max_cluster_size,
            cluster_size_sum,
            column_diversity,
            row_height,
            stair_level,
            flatness,
            isolated,
            COUNT
        };

        using PARAM_TYPE = double;

        const std::vector<POSi> STAIR_DIR;
        const PARAM_TYPE MIN_VALUE;
        const std::array<int, COUNT> signs;

        const int& curr_score;
        int prev_score;
        int prev_color_puyo_sum;

        std::array<PARAM_TYPE, COUNT> weights;
        std::array<PARAM_TYPE, COUNT> parameters_sum;
        int N_count;
        std::array<PARAM_TYPE, COUNT> parameters_mean;
        std::array<PARAM_TYPE, COUNT> parameters_stdev;

        std::vector<PARAM_TYPE> expected_mean_scores;
        std::vector<int> expected_mean_count;

        PARAM_TYPE get_ratio(ParameterName name, PARAM_TYPE x);
        PARAM_TYPE get_new_mean(ParameterName name, PARAM_TYPE x);
        PARAM_TYPE get_new_stdev(ParameterName name, PARAM_TYPE old_mean, PARAM_TYPE x);
        PARAM_TYPE get_bias();

        std::pair<PARAM_TYPE, PARAM_TYPE> get_cluster_sizes(const std::vector<puyoPuyo>& deployed_puyos);
        PARAM_TYPE get_column_diversity(const std::vector<puyoPuyo>& deployed_puyos);
        PARAM_TYPE get_row_height(const std::vector<puyoPuyo>& deployed_puyos);
        PARAM_TYPE get_stair_level(const std::vector<puyoPuyo>& deployed_puyos);
        PARAM_TYPE get_flatness(const std::vector<puyoPuyo>& deployed_puyos);
        PARAM_TYPE get_isolated(const std::vector<puyoPuyo>& deployed_puyos);

        PARAM_TYPE get_expected_mean_score(int color_puyo_sum, int dscore);
        PARAM_TYPE sigmoid(PARAM_TYPE score, PARAM_TYPE expected_min_score);
        PARAM_TYPE is_activated(PARAM_TYPE value);
        void backpropagation(int color_puyo_sum);

        int simulate_chain(const puyoPlayer& player, POSi simul_droos);
        int get_potential(const puyoPlayer& player, const std::vector<POSi>& deployed_puyos);
    public :
        puyoBotModel2(const int& curr_score, POSi bsize, unsigned int act_time_unit = 0);     
        ~puyoBotModel2() override; 

        void saveModel(const std::string& filename);
        void loadModel(const std::string& filename);

        void think_perfect_lets(const puyoPlayer& player) override;
};