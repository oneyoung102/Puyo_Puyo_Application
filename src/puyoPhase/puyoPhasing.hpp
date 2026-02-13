#pragma once

#include <vector>
#include <random>
#include <memory>

#include "puyoPlayer.hpp"

using namespace std;

class puyoPlayPuyo;
class puyoTempPuyo;
class puyoBoard;

class puyoPhasing
{
    private :
        vector<unique_ptr<puyoPlayer>> players;
        vector<pair<int,int>> new_colors;

        vector<pair<int,int>> dir; //queue를 위해
        int condition_for_vanish;

        bool game_end;

        int gravity_value, vanish_value;
        int delay_time;

        bool is_play_time(puyoBoard& board);
        bool is_gravity_time(puyoBoard& board);
        bool is_vanish_time(puyoBoard& board);

    public :
        puyoPhasing();


        void act_play_puyo(puyoBoard& board, puyoPlayPuyo& puyo);///
        void gravity_gravity_puyos(puyoBoard& board);
        void vanish_vanish_puyo(puyoBoard& board);
        void find_gravity_puyo(puyoBoard& board);
        void find_vanish_puyo(puyoBoard& board);

        void delay(int time);
        void wait();
        bool is_delayed();

        void end_game();////

        pair<int,int> get_new_puyo_color(int count);

        void set_condition_for_vanish(int amount);
        int get_condition_for_vanish();

        void set_game();
        void proceed_game();
        bool game_ended();

        int get_player_count();
        vector<unique_ptr<puyoPlayer>>&& get_players();
};