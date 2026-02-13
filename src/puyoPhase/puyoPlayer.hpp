#pragma once

#include "puyoBoard.hpp"
#include "puyoPlayPuyo/puyoPlayPuyo.hpp"

#include <vector>
#include <tuple>
#include <functional>

using namespace std;

class puyoPlayer
{
    public :
        enum class Statement{
            play,
            gravity,
            vanish
        };
    private :
        puyoBoard board;
        puyoPlayPuyo puyo;

        int player_num; // 0 또는 1
        int new_puyo_count;

        int puyo_gravity_value;
        Statement statement;

    public :

        puyoPlayer(int pn, puyoBoard&& b, puyoPlayPuyo&& p);


        int get_player_num();
        puyoBoard& get_board();
        puyoPlayPuyo& get_puyo();

        void give_new_puyo(pair<int,int> colors);
        int get_new_puyo_count();

        pair<float,float> get_puyo_spawn_pos();
        void set_puyo_spawn_pos(float x, float y);
        int get_puyo_gravity_value();
        void set_puyo_gravity_value(int v);

        function<void()> get_let_left();
        function<void()> get_let_right();
        function<void()> get_let_down();
        //function<void()> get_let_up();
        function<void()> get_let_turn();
        function<void()> get_let_drop();

        Statement get_statement();
        void convert_statement(Statement s);
};