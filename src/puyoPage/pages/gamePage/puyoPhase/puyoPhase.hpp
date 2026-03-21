
#pragma once

#include <vector>
#include <random>
#include <memory>

#include "puyoPage/pages/gamePage/puyoPlayer/puyoPlayer.hpp"
#include "puyoPage/pages/gamePage/puyoPhase/puyoScoreCalc.hpp"
#include "puyoPage/puyoPageManager/puyoPageSignal.hpp"

#include "puyoPage/pages/gamePage/puyoPhase/puyoMode/puyoMode.hpp"

class puyoPlayPuyo;
class puyoTempPuyo;
class puyoBoard;

class puyoPhase
{
    private :
        enum class Phase{
            play,
            gravity,
            vanish
        };
        Phase get_phase(puyoBoard& board);

        std::vector<std::unique_ptr<puyoPlayer>> players;
        std::vector<int> delay_times;
        
        std::mt19937 gen;
        std::vector<std::pair<int,int>> new_colors;

        puyoScoreCalc calc;

        bool game_end;
        int win_player_num;

        std::unique_ptr<puyoMode> curr_mode; 
        int gravity_value, stay_value, color_count;

        void delay(int player_num,int time);
        void wait(int player_num);
        bool is_delayed(int player_num);

    public :
        puyoPhase();

        void end_game();////

        std::pair<int,int> get_new_puyo_color(int count);
        std::vector<std::pair<int,int>>& get_new_colors();

        void set_game(Diff diff, Mode mode);
        void proceed_game();
        bool game_ended();

        int get_player_count();
        std::vector<std::unique_ptr<puyoPlayer>>&& get_players();
        void add_player(std::unique_ptr<puyoPlayer>&& player);
        int get_gravity_value();
        void set_gravity_value(int value);
        int get_stay_value();
        void set_stay_value(int value);
        int get_color_count();
        void set_color_count(int value);

        int get_win_player_num();
};