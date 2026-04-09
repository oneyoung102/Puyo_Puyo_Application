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
        double puyo_spawn_x;
        double puyo_spawn_y;
    public :  
        puyoBoard();

        void set_spawn_pos(double x, double y);
        std::pair<double,double> get_spawn_pos() const;
        
        std::pair<int,int> get_size() const;
        bool in_row(int r) const;
        bool in_col(int c) const;
        bool in(int r, int c) const;
        bool touched(int r, int c) const;

        puyoType get_puyo(int r, int c) const;//이건 행,열
        void insert_puyo(puyoType puyo, int r, int c);//이건 행,열
        void remove_puyo(int r, int c);//이건 행,열
        bool empty() const;
        bool all_cleared();

        puyoBoardEnergyControll& controll_energy();
        puyoBoardGravityControll& controll_gravity();
        puyoBoardScoreControll& controll_score();
        puyoBoardObstructControll& controll_obstuct();
        puyoBoardVanishControll& controll_vanish();
        puyoBoardFutureControll& controll_future();
};