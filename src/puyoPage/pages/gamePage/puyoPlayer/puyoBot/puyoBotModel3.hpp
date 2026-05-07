#pragma once

#include "puyoPage/pages/gamePage/puyoPlayer/puyoBot/puyoBot.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/puyoType.hpp"
#include "puyoTool/puyoPos.hpp"
#include <vector>

class puyoBotModel3 : public puyoBot
{
    private :
        const std::vector<std::pair<puyoType,puyoType>>& new_types;
        const int& next_puyo_count;
        const int beam_search_select_count;

        int simulate_chain(POSi simul_droos, int vanish_condition);
        int get_potential(int vanish_condition, const std::vector<POSi>& deployed_puyos);
        bool fire_able(int vanish_condition, const std::vector<POSi>& deployed_puyos);
        std::pair<int,PROBABLITY> beam_search(const puyoBoard& board, const puyoPlayPuyo& puyo, const std::vector<std::pair<puyoType,puyoType>>& next_types, int count, const bool fire);
    public :
        puyoBotModel3(const std::vector<std::pair<puyoType,puyoType>>& new_types, const int& next_puyo_count, POSi bsize, unsigned int act_time_unit = 0);     
        void think_perfect_lets(const puyoBoard& board, const puyoPlayPuyo& puyo) override;
};