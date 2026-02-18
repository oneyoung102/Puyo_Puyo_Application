#pragma once

#include <vector>
#include <utility>
#include <set>
#include <random>
#include "puyoTempPuyo/puyoGravityPuyo.hpp"
#include "puyoTempPuyo/puyoVanishPuyo.hpp"
#include "puyoTempPuyo/puyoFuturePuyo.hpp"

#include "puyoPlayPuyo/puyoPlayPuyo.hpp"

using namespace std;

class puyoBoard
{
    public :
        enum class Type
        {
            blank = -1,
            red,
            green,
            blue,
            yellow,
            pupple,
            obstruct
        };
    private :
        vector<puyoGravityPuyo> gravity_puyos;
        vector<puyoVanishPuyo> vanish_puyos;
        vector<puyoFuturePuyo> future_puyos;
        int obstruct_puyo,obstruct_puyo_max;
        mt19937 gen;
        
        vector<vector<Type>> board;
        const int board_r, board_c; 
        float puyo_spawn_x;
        float puyo_spawn_y;

        bool gravity_puyo_is_out_in_board;

        vector<pair<int,int>> dir; //queue를 위해
        int condition_for_vanish;
        int gravity_value, vanish_value;

        int puyo_count, chain_count;//점수 계산용 
        vector<int> link_count;//점수 계산용 
        set<Type> color_count;//점수 계산용 

        bool chain_signal, all_cleared_signal;

    public :  
        puyoBoard();

        void set_puyo_spawn_pos(float x, float y);
        pair<float,float> get_puyo_spawn_pos();
        
        pair<int,int> get_board_size();
        bool is_in_row(int r);
        bool is_in_col(int c);
        bool is_in_board(int r, int c);

        Type get_puyo(int r, int c);//이건 행,열
        void insert_puyo(Type puyo, int r, int c);//이건 행,열
        void remove_puyo(int r, int c);//이건 행,열

        void find_gravity_puyo();
        void find_vanish_puyo();
        void find_future_puyos(puyoPlayPuyo& puyo);
        void remove_future_puyos();

        void give_obstruct_puyo(int count);
        void spawn_obstruct_puyo();
        bool not_existed_obstructed_puyo();
        int& get_obstruct_puyo();

        void gravity_gravity_puyos();
        void vanish_vanish_puyo();

        int get_chain_count();
        void add_chain_count();
        void reset_chain_count();
        int get_puyo_count();
        vector<int> get_link_count();
        int get_color_count();

        void push_gravity_puyo(puyoGravityPuyo&& ptp);
        void push_gravity_puyo(vector<puyoGravityPuyo>&& ptp_v);
        void push_vanish_puyo(puyoVanishPuyo&& ptp);

        void set_condition_for_vanish(int amount);
        int get_condition_for_vanish();

        vector<puyoGravityPuyo>& get_gravity_puyos();
        vector<puyoVanishPuyo>& get_vanish_puyos();
        vector<puyoFuturePuyo>& get_future_puyos();
        bool not_existed_gravity_puyo();
        bool not_existed_vanish_puyo();
        bool gravity_puyo_is_out();

        bool is_all_cleared();
        bool chain_signal_for_printing();
        bool all_cleared_signal_for_printing();
};