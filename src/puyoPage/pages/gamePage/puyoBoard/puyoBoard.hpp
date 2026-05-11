#pragma once

#include <vector>

#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/puyoType.hpp"
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
    unfreeze,
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
        const POSi size; 
        POSf spawn_pos;
    public :  
        puyoBoard();

        void set_spawn_pos(POSf pos);
        POSf get_spawn_pos() const;
        bool spawn_able() const;
        
        POSi get_size() const;
        bool in_row(int r) const;
        bool in_col(int c) const;
        bool in(POSi pos) const;
        bool touched(POSi pos) const;

        puyoType get_puyo(POSs pos) const;
        puyoType& ref_puyo(POSs pos);
        void insert_puyo(puyoType puyo, POSs pos);
        void remove_puyo(POSs pos);
        bool empty() const;
        bool empty(POSs pos) const;
        bool all_cleared();
        std::vector<_puyoType::typeState> update();

        std::vector<PUYO_INFO> to_gravity_puyo();

        puyoBoardEnergyControll& controll_energy();
        puyoBoardGravityControll& controll_gravity();
        puyoBoardScoreControll& controll_score();
        puyoBoardObstructControll& controll_obstuct();
        puyoBoardVanishControll& controll_vanish();
        puyoBoardFutureControll& controll_future();

        const puyoBoardEnergyControll& controll_energy() const;
        const puyoBoardGravityControll& controll_gravity() const;
        const puyoBoardScoreControll& controll_score() const;
        const puyoBoardObstructControll& controll_obstuct() const;
        const puyoBoardVanishControll& controll_vanish() const;
        const puyoBoardFutureControll& controll_future() const;
};