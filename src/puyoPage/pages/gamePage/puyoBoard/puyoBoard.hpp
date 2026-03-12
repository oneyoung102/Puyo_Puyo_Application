#pragma once

#include <vector>
#include <utility>
#include <set>
#include "puyoPage/pages/gamePage/puyoTempPuyo/puyoGravityPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoTempPuyo/puyoVanishPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoTempPuyo/puyoFuturePuyo.hpp"
#include "puyoPage/pages/gamePage/puyoTempPuyo/puyoEnergyPuyo.hpp"

#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoPage/puyoObjectSignal.hpp"

using namespace std;

enum class puyoBoardSignal
{
    chain,
    all_cleared,
    spawn_obsp,
    vanished,
    COUNT
};

class puyoBoard : public puyoObjectSignal<puyoBoardSignal>
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
        vector<tuple<int,int,int>> temp_energy_puyos; 
        vector<puyoEnergyPuyo> energy_puyos; 
        int obstruct_puyo;
        
        vector<vector<Type>> board;
        const int board_r, board_c; 
        float puyo_spawn_x;
        float puyo_spawn_y;

        bool gravity_puyo_is_out_in_board;

        vector<pair<int,int>> dir; //queue를 위해
        int condition_for_vanish;

        int puyo_count, chain_count;//점수 계산용 
        vector<int> link_count;//점수 계산용 
        set<Type> color_count;//점수 계산용 

        int temp_obstruct_puyo; //방해뿌요 소리를 위한 임시 방해뿌요 개수
        bool approvement_for_obstruct_puyo;

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
        void find_energy_puyos(float fx, float fy, float tx, float ty);// temp_energy_puyo를 energy_puyo로
        void clear_temp_energy_puyos();

        void give_obstruct_puyo(int count);
        void spawn_obstruct_puyo(int obstruct_puyo_for_dropping);
        bool obstructed_puyo_empty();
        int& get_obstruct_puyo();

        void gravity_gravity_puyos();
        void vanish_vanish_puyos();
        void fly_energy_puyos();

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
        vector<puyoEnergyPuyo>& get_energy_puyos();
        bool gravity_puyo_empty();
        bool vanish_puyo_empty();
        bool temp_energy_puyo_empty();
        bool gravity_puyo_is_out();

        bool is_empty();
        bool is_all_cleared();

        int get_temp_obstruct_puyo_for_sounding();
        void approve_spawn_obstruct_puyo();
};