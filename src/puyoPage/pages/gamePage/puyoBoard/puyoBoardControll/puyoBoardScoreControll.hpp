#pragma once

#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/types/_puyoType.hpp"
#include <vector>
#include <set>

class puyoBoard;

class puyoBoardScoreControll
{
    private :
        int puyo_count, chain_count;//점수 계산용 
        std::vector<int> link_count;//점수 계산용 
        std::set<_puyoType::Type> color_count;//점수 계산용 
    public :
        puyoBoardScoreControll();

        int get_chain_count();
        void add_chain_count(puyoBoard& board);
        void reset_chain_count();

        int get_puyo_count();
        void add_puyo_count(int count);

        std::vector<int> get_link_count();
        void add_link_count(int count);
        void add_link_count(const std::vector<int>& counts);

        int get_color_count();
        void add_color_count(_puyoType::Type type);
        void add_color_count(const std::vector<_puyoType::Type>& types);
};