#pragma once

#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"

class puyoPrintSpawnspot : public puyoPrintObject
{
    private :
        const int SPAWN_SPOT_CYCLE;
        const int player_num;
        int spawn_spot_state;
        bool spawn_spot_rotate_dir;
    public :
        puyoPrintSpawnspot(int player_num, sf::Sprite screen, std::pair<float,float> pos, int life);
        void print(sf::RenderWindow &w) override;
};