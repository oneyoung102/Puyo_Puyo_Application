#pragma once

#include "puyoPage/pages/gamePage/puyoBoard/puyoType.hpp"
#include "puyoPage/pages/gamePage/puyoPhase/puyoMode/puyoMode.hpp"
#include <random>

class puyoModeBomb : public puyoMode
{
    private :
        int bomb_have_player_num;
        bool bomb_is_spawned;
        int bomb_tick;
        puyoType bomb_appearance;
        int bomb_c;//폭탄이 위치한 열

        std::mt19937 gen;
    public :
        puyoModeBomb(int player_count);
        void proceed_mode(puyoPhase& phase, puyoPlayer& player) override;
};