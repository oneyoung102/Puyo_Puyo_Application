#pragma once

#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/puyoType.hpp"
#include <vector>
#include <set>

class puyoBoard;

class puyoScoreControll
{
    private :
        int puyo_count, chain_count;
        std::vector<int> link_count;
        std::set<puyoType::Type> color_count;

        int obstruct_puyo_rate;
        int all_cleared_obstruct_puyo;
        
    public :
        puyoScoreControll();

        int get_drop_score(const std::vector<puyoPuyo>& future_puyos, const puyoPlayPuyo& play_puyo) const;

        int get_chain_count() const;
        void add_chain_count();
        void reset_chain_count();

        void add_puyo_count(int count);

        void add_link_count(int count);
        void add_link_count(std::vector<int>&& counts);

        void add_color_count(puyoType::Type type);
        void add_color_count(std::vector<puyoType::Type>&& types);

        int get_add_score();
        int get_opposite_obstruct_puyo(int self, int opp) const;
        int to_obstruct_puyo(int score) const;

        void set_obstruct_puyo_rate(int value = puyoGameConstant::BASIC_OBSTRCUT_RATE);
        void set_all_cleared_obstruct_puyo(int value = puyoGameConstant::BASIC_ALL_CLEARED_OBSTRUCT_PUYO);
        int get_all_cleared_score() const;
        int get_obstruct_puyo_for_dropping(int obstruct_puyo) const;
};