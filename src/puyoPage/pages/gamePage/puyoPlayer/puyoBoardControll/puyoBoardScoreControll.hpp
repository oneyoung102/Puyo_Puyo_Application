#pragma once

#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/puyoType.hpp"
#include <vector>
#include <set>

class puyoBoard;

class puyoBoardScoreControll
{
    private :
        int puyo_count, chain_count;
        std::vector<int> link_count;
        std::set<puyoType::Type> color_count;
    public :
        puyoBoardScoreControll();

        int get_drop_score(const std::vector<puyoPuyo>& future_puyos, const puyoPlayPuyo& play_puyo) const;

        int get_chain_count() const;
        void add_chain_count();
        void reset_chain_count();

        int get_puyo_count();
        void add_puyo_count(int count);

        std::vector<int> get_link_count();
        void add_link_count(int count);
        void add_link_count(std::vector<int>&& counts);

        int get_color_count();
        void add_color_count(puyoType::Type type);
        void add_color_count(std::vector<puyoType::Type>&& types);
};