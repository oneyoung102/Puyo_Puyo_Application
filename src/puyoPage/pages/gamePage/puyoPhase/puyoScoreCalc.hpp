#pragma once

#include <vector>

class puyoScoreCalc
{
    private : 
        int obstruct_puyo_rate;
        int all_cleared_obstruct_puyo;
        std::vector<int> chain_bonus, link_bonus, color_bonus;
    public : 
        puyoScoreCalc();
        int get_add_score(int puyo, int chain, const std::vector<int>& link, int color);
        int get_opposite_obstruct_puyo_count(int self, int opp);
        int to_obstruct_puyo(int score);
        void set_obstruct_puyo_rate(int v);
        int get_all_cleared_score();
        int get_obstruct_puyo_for_dropping(int obstruct_puyo);
};