#pragma once

#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoType.hpp"
#include <vector>

class puyoBoard;

class puyoBoardVanishControll
{
    private :
        int condition_for_vanish;
        std::vector<puyoPuyo> vanish_puyos;
        const std::vector<std::pair<int,int>> dir; //queue를 위해
    public :
        puyoBoardVanishControll();
        void make_vanish(puyoBoard& board, int x, int y, puyoType type, int tick);
        void find(puyoBoard& board);
        void vanish(puyoBoard& board);
        void add(PUYO_INFO puyo);

        void set_condition(int amount);
        int get_condition();

        std::vector<puyoPuyo>& get();
        bool empty();
};