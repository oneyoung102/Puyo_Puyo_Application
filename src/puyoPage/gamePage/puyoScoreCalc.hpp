#pragma once

#include <vector>
#include <utility>

class puyoScoreCalc
{
    private : 
        int obstruct_puyo_rate;
        int all_cleared_obstruct_puyo;
        std::vector<int> chain_bonus, link_bonus, color_bonus;
    public : 
        puyoScoreCalc();
        int get_add_score(int puyo, int chain, std::vector<int> link, int color);
        std::pair<int,int> get_obstruct_puyo_count(int self_obstruct_puyo_count, int curr_obstruct_puyo_count);
        int score_to_obstruct_puyo(int score);
        void set_obstruct_puyo_rate(int v);
        int get_all_cleared_obstruct_puyo();
};