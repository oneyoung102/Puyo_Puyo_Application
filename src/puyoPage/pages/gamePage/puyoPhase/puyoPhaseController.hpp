#pragma once

#include "puyoPage/pages/gamePage/puyoPlayer/puyoPlayer.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include <vector>

class puyoPhaseController
{
    public :
        enum class Phase{
            play,
            gravity,
            vanish
        };
    private :
        std::vector<Phase> curr_phases;
        std::vector<int> delay_times;
    public :
        puyoPhaseController(size_t player_count = 0);
        
        Phase get_phase(int player_num) const;
        void set_phase(int player_num, Phase phase);
        bool is_phase(int player_num, Phase phase) const;

        void delay(int player_num, int time);
        void wait(int player_num);
        bool delayed (int player_num) const;

        void act_play_puyo(puyoPlayer& player);
        int do_after_puyo_dropped(puyoPlayer& player, std::pair<puyoPuyo,puyoPuyo>&& new_puyos, int gravity_value, int stay_value);
        bool act_gravity_puyos(puyoPlayer& player);
        bool test_and_prepare_vanish(puyoPlayer& player);
        bool act_vanish_puyos(puyoPlayer& player);
        bool test_and_prepare_gravity(puyoPlayer& player);
        bool test_spawn_obstruct_puyo(puyoPlayer& player, int obstruct_puyo_for_dropping);
};