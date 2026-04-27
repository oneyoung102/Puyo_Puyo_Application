#pragma once

#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

class puyoPrintSpawnspot : public puyoPrintObject
{
    private :
        const int player_num;
        int spawn_spot_state;
        bool spawn_spot_rotate_dir;
    public :
        puyoPrintSpawnspot(int player_num, sf::Sprite screen, POSf pos, int life = puyoImageConstant::PRINT_IMMORTAL);
        void print(sf::RenderWindow &w) override;
};