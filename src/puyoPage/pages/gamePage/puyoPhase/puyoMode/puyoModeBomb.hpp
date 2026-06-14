#pragma once

#include "puyoPage/pages/gamePage/puyoPhase/puyoMode/puyoMode.hpp"
#include <random>

class puyoModeBomb : public puyoMode
{
    private :
        int bomb_have_player_num;
        bool bomb_is_spawned;
        size_t bomb_c;

        std::mt19937 gen;
    public :
        puyoModeBomb(int player_count);
        void proceed_mode(puyoPhase& phase, puyoPlayer& player) override;
};