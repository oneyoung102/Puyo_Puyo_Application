#pragma once

#include <vector>
#include <utility>
#include "puyoTempPuyo/puyoGravityPuyo.hpp"
#include "puyoTempPuyo/puyoVanishPuyo.hpp"

using namespace std;


class puyoBoard
{
    private :
        vector<puyoGravityPuyo> gravity_puyos;
        vector<puyoVanishPuyo> vanish_puyos;
        vector<vector<int>> board;
        const int board_r, board_c; 
        float puyo_spawn_x;
        float puyo_spawn_y;

    public :  
        puyoBoard();

        void set_puyo_spawn_pos(float x, float y);
        pair<float,float> get_puyo_spawn_pos();
        
        pair<int,int> get_board_size();
        bool is_in_row(int r);
        bool is_in_col(int c);
        bool is_in_board(int r, int c);

        int get_puyo(int r, int c);//이건 행,열
        void insert_puyo(int puyo, int r, int c);//이건 행,열
        void remove_puyo(int r, int c);//이건 행,열

        void push_gravity_puyo(puyoGravityPuyo&& ptp);
        void push_gravity_puyo(vector<puyoGravityPuyo>&& ptp_v);
        void push_vanish_puyo(puyoVanishPuyo&& ptp);

        vector<puyoGravityPuyo>& get_gravity_puyos();
        vector<puyoVanishPuyo>& get_vanish_puyos();
        bool not_existed_gravity_puyo();
        bool not_existed_vanish_puyo();
};