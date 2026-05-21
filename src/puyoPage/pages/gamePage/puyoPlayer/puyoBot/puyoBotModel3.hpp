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
        const std::vector<std::pair<puyoPuyo,puyoPuyo>>& new_types;
        const int& next_puyo_count;
        const int beam_search_select_count;

        int simulate_chain(const puyoPlayer& player, POSi simul_droos);
        int get_potential(const puyoPlayer& player, const std::vector<puyoPuyo>& deployed_puyos);
        bool fire_able(const puyoPlayer& player, const std::vector<puyoPuyo>& deployed_puyos);
        std::pair<int,PROBABLITY> beam_search(const puyoPlayer& player, const puyoBoard& board, const std::vector<std::pair<puyoPuyo,puyoPuyo>>& next_types, int count, const bool fire);
    public :
        puyoBotModel3(const std::vector<std::pair<puyoPuyo,puyoPuyo>>& new_types, const int& next_puyo_count, POSi bsize, unsigned int act_time_unit = 0);     
        void think_perfect_lets(const puyoPlayer& player) override;
};