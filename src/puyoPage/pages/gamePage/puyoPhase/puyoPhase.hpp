
#pragma once

#include <vector>
#include <random>
#include <memory>

#include "puyoPage/pages/gamePage/puyoPlayer/puyoPlayer.hpp"
#include "puyoPage/pages/gamePage/puyoPhase/puyoScoreCalc.hpp"

using namespace std;

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
        vector<unique_ptr<puyoPlayer>> players;
        vector<int> delay_times;
        
        mt19937 gen;
        vector<pair<int,int>> new_colors;

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

        pair<int,int> get_new_puyo_color(int count);
        vector<pair<int,int>>& get_new_colors();

        void set_game(float spawn_x, float spawn_y, int condition, int gravity, int stay, int cc);
        void proceed_game();
        bool game_ended();

        int get_player_count();
        vector<unique_ptr<puyoPlayer>>&& get_players();
        void add_player(unique_ptr<puyoPlayer>&& player);

        int get_win_player_num();
};