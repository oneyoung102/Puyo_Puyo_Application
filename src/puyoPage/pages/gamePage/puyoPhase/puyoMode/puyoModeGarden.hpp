#pragma once

#include "puyoPage/pages/gamePage/puyoPhase/puyoMode/puyoMode.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/puyoType.hpp"
#include <random>
#include <stack>
#include <vector>

class puyoModeGarden : public puyoMode
{
    private :
        enum class Spawn
        {
            none,
            seed,
            water
        };
        int cycle;
        std::stack<Spawn> seeds;
        std::vector<bool> spawned;
        
        std::mt19937 gen;
    public :
        puyoModeGarden();
        void proceed_mode(puyoPhase& phase, puyoPlayer& player) override;
};