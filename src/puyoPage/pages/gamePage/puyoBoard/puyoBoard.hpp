#pragma once

#include <vector>

#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/puyoType.hpp"
#include "puyoPage/puyoObjectSignal/puyoObjectSignal.hpp"

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
        std::vector<std::vector<puyoPuyo>> board;
        const POSi size; 
        POSf spawn_pos;
    public :  
        puyoBoard();

        void set_spawn_pos(const POSf& pos);
        POSf get_spawn_pos() const;
        bool spawn_able() const;
        
        POSi get_size() const;
        bool in_row(int r) const;
        bool in_col(int c) const;
        bool in(const POSi& pos) const;
        bool touched(const POSi& pos) const;

        const puyoPuyo& get_puyo(const POSs& pos) const;
        puyoPuyo& ref_puyo(const POSs& pos);
        puyoPuyo& operator[](const POSs& pos);
        
        void insert_puyo(const puyoPuyo& puyo, const POSs& pos);
        void insert_puyo(const puyoPuyo& puyo);
        void insert_puyo(puyoPuyo&& puyo, const POSs& pos);
        void insert_puyo(puyoPuyo&& puyo);

        void remove_puyo(const POSs& pos);
        bool empty(const POSs& pos) const;
        bool all_cleared();
        std::vector<puyoType::typeState> update();

        std::vector<puyoPuyo> to_gravity_puyo();
        puyoPuyo to_vanish_puyo(const POSs& pos);
        
};