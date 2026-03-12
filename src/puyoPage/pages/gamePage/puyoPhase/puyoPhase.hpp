
#pragma once

#include <vector>
#include <random>
#include <memory>

#include "puyoPage/pages/gamePage/puyoPlayer/puyoPlayer.hpp"
#include "puyoPage/pages/gamePage/puyoPhase/puyoScoreCalc.hpp"

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
        std::vector<std::unique_ptr<puyoPlayer>> players;
        std::vector<int> delay_times;
        
        std::mt19937 gen;
        std::vector<std::pair<int,int>> new_colors;

        puyoScoreCalc calc;

        bool game_end;
        int win_player_num;

        int color_count;//색 종류

        Phase get_phase(puyoBoard& board);

        void delay(int player_num,int time);
        void wait(int player_num);
        bool is_delayed(int player_num);

    public :
        puyoPhase();

        void end_game();////

        std::pair<int,int> get_new_puyo_color(int count);
        std::vector<std::pair<int,int>>& get_new_colors();

        void set_game(float spawn_x, float spawn_y, int condition, int gravity, int stay, int cc);
        void proceed_game();
        bool game_ended();

        int get_player_count();
        std::vector<std::unique_ptr<puyoPlayer>>&& get_players();
        void add_player(std::unique_ptr<puyoPlayer>&& player);

        int get_win_player_num();
};