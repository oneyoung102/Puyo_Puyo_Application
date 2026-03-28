#pragma once

#include <vector>

#include "puyoPage/pages/gamePage/puyoBoard/puyoType.hpp"
#include "puyoPage/puyoObjectSignal.hpp"

#include "puyoPage/pages/gamePage/puyoBoard/puyoBoardControll/puyoBoardEnergyControll.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoBoardControll/puyoBoardGravityControll.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoBoardControll/puyoBoardScoreControll.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoBoardControll/puyoBoardVanishControll.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoBoardControll/puyoBoardFutureControll.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoBoardControll/puyoBoardObstructControll.hpp"

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
    private :
        puyoBoardEnergyControll energy_controll;
        puyoBoardGravityControll gravity_controll;
        puyoBoardScoreControll score_controll;
        puyoBoardObstructControll obstuct_controll;
        puyoBoardVanishControll vanish_controll;
        puyoBoardFutureControll future_controll;
        
        std::vector<std::vector<puyoType>> board;
        const int board_r, board_c; 
        float puyo_spawn_x;
        float puyo_spawn_y;
    public :  
        puyoBoard();

        void set_puyo_spawn_pos(float x, float y);
        std::pair<float,float> get_puyo_spawn_pos();
        
        std::pair<int,int> get_board_size();
        bool is_in_row(int r);
        bool is_in_col(int c);
        bool is_in_board(int r, int c);

        puyoType get_puyo(int r, int c);//이건 행,열
        void insert_puyo(puyoType puyo, int r, int c);//이건 행,열
        void remove_puyo(int r, int c);//이건 행,열
 
        bool is_empty();
        bool is_all_cleared();

        puyoBoardEnergyControll& controll_energy();
        puyoBoardGravityControll& controll_gravity();
        puyoBoardScoreControll& controll_score();
        puyoBoardObstructControll& controll_obstuct();
        puyoBoardVanishControll& controll_vanish();
        puyoBoardFutureControll& controll_future();
};