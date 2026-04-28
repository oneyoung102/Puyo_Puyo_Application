#pragma once

#include "puyoPage/pages/gamePage/puyoPuyo/puyoType.hpp"
#include "puyoPage/pages/gamePage/puyoPhase/puyoMode/puyoMode.hpp"
#include <random>

class puyoModeBomb : public puyoMode
{
    private :
        int bomb_have_player_num;
        bool bomb_is_spawned;
        int bomb_tick;
        puyoType bomb_appearance;
        size_t bomb_x;//폭탄이 위치한 x

        std::mt19937 gen;
    public :
        puyoModeBomb(int player_count);
        void proceed_mode(puyoPhase& phase, const puyoPlayer& player) override;
};