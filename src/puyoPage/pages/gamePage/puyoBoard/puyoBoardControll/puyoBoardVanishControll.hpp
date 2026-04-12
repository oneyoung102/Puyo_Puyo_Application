#pragma once

#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType.hpp"
#include <vector>

class puyoBoard;

class puyoBoardVanishControll
{
    private :
        int condition_for_vanish;
        std::vector<puyoPuyo> vanish_puyos;
        const std::vector<std::pair<int,int>> dir; //queue를 위해
        void add(PUYO_INFO puyo);
    public :
        puyoBoardVanishControll();
        void to_vanish_puyo(puyoBoard& board, PUYO_INFO puyo);
        void find(puyoBoard& board);
        void vanish(puyoBoard& board);

        void set_condition(int amount);
        int get_condition() const;

        const std::vector<puyoPuyo>& get() const;
        bool empty() const;
};