#pragma once

#include "puyoBoard.hpp"
#include "puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "../puyoObjectSignal.hpp"
#include "puyoBotAlgorithm.hpp"

#include <utility>
#include <functional>
#include <memory>

using namespace std;

enum class puyoPlayerSignal
{
    puyo_dropped,
    COUNT
};

class puyoPlayer : public puyoObjectSignal<puyoPlayerSignal>
{
    private :
        puyoBoard board;
        puyoPlayPuyo puyo;
        int score, opposite_obstruct_puyo_count/*상대에게 보낼 방해 뿌요*/;

        int player_num; // 0 또는 1
        int new_puyo_count;

        int puyo_gravity_value,puyo_stay_value;
        bool player_is_bot;
        unique_ptr<puyoBotAlgorithm> bot_algorithm;

    public :

        puyoPlayer(int pn, puyoBoard&& b, puyoPlayPuyo&& p,bool temp_player_is_bot);


        int get_player_num();
        puyoBoard& get_board();
        puyoPlayPuyo& get_puyo();

        int& get_score();
        void add_score(int s);
        int get_opposite_obstruct_puyo_count();
        void add_opposite_obstruct_puyo_count(int c);
        void clear_opposite_obstruct_puyo_count();

        void give_new_puyo(pair<int,int> colors);
        int& get_new_puyo_count();

        pair<float,float> get_puyo_spawn_pos();
        void set_puyo_spawn_pos(float x, float y);
        int get_puyo_gravity_value();
        void set_puyo_gravity_value(int v);
        int get_puyo_stay_value();
        void set_puyo_stay_value(int v);
        int get_condition_for_vanish();
        void set_condition_for_vanish(int amount);

        function<void()> get_let_left();
        function<void()> get_let_right();
        function<void()> get_let_down();
        //function<void()> get_let_up();
        function<void()> get_let_turn();
        function<void()> get_let_drop();

        void sign_play_puyo_dropped();

        bool is_bot();
        void act_bot_let();
};