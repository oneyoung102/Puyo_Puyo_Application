#pragma once

#include <vector>

class puyoScoreCalc
{
    private : 
        int obstruct_puyo_rate;
        int all_cleared_obstruct_puyo;
        static std::vector<int> chain_bonus, link_bonus, color_bonus;
    public : 
        puyoScoreCalc();
        int get_add_score(int puyo, int chain, std::vector<int>&& links, int color) const;
        int get_opposite_obstruct_puyo(int self, int opp) const;
        int to_obstruct_puyo(int score) const;
        void set_obstruct_puyo_rate(int v);
        int get_all_cleared_score() const;
        int get_obstruct_puyo_for_dropping(int obstruct_puyo) const;
};