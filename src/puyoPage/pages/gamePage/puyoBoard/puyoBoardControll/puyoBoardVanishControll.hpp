#pragma once

#include "puyoPage/pages/gamePage/puyoTempPuyo/puyoVanishPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoType.hpp"
#include <vector>

class puyoBoard;

class puyoBoardVanishControll
{
    private :
        int condition_for_vanish;
        std::vector<puyoVanishPuyo> vanish_puyos;
        const std::vector<std::pair<int,int>> dir; //queue를 위해
    public :
        puyoBoardVanishControll();
        void vanish_deployed_puyo(puyoBoard& board, int x, int y, puyoType type, int tick);
        void find_vanish_puyo(puyoBoard& board);
        void vanish_vanish_puyos(puyoBoard& board);
        void push_vanish_puyo(puyoVanishPuyo&& ptp);

        void set_condition_for_vanish(int amount);
        int get_condition_for_vanish();

        std::vector<puyoVanishPuyo>& get_vanish_puyos();
        bool vanish_puyo_empty();
};