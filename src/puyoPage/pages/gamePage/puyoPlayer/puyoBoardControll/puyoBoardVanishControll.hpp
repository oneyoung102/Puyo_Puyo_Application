#pragma once

#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include <vector>

class puyoBoard;

class puyoBoardVanishControll
{
    private :
        int condition_for_vanish;
        std::vector<puyoPuyo> vanish_puyos;
    public :
        puyoBoardVanishControll();
        void add(puyoPuyo&& puyo);
        
        std::tuple<int, int, std::vector<POSs>> fire_cluster(const puyoBoard& board, const POSs& fire_pos, std::vector<std::vector<bool>>& visited) const;
        std::tuple<int, std::vector<int>, std::vector<puyoType::Type>,std::vector<puyoPuyo>> to_vanish_puyo(puyoBoard& board);
        void vanish(puyoBoard& board);

        void set_condition(int amount);
        int get_condition() const;

        const std::vector<puyoPuyo>& get() const;
        bool empty() const;
};