#pragma once

#include <vector>

#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType.hpp"
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
    many_obsp_dropped,
    mid_obsp_dropped,
    less_obsp_dropped,
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
        POS spawn_pos;
    public :  
        puyoBoard();

        void set_spawn_pos(POS pos);
        POS get_spawn_pos() const;
        
        std::pair<int,int> get_size() const;
        bool in_row(int r) const;
        bool in_col(int c) const;
        bool in(int r, int c) const;
        bool touched(int r, int c) const;

        puyoType get_puyo(int r, int c) const;//이건 행,열
        void insert_puyo(puyoType puyo, int r, int c);//이건 행,열
        void remove_puyo(int r, int c);//이건 행,열
        bool empty() const;
        bool empty(int r, int c) const;
        bool all_cleared();

        std::vector<PUYO_INFO> to_gravity_puyo();

        puyoBoardEnergyControll& controll_energy();
        puyoBoardGravityControll& controll_gravity();
        puyoBoardScoreControll& controll_score();
        puyoBoardObstructControll& controll_obstuct();
        puyoBoardVanishControll& controll_vanish();
        puyoBoardFutureControll& controll_future();
};