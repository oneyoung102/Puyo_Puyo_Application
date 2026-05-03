#pragma once

#include "puyoTool/puyoDir.hpp"
#include "puyoTool/puyoPos.hpp"
#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

class puyoPrintSpawnspot : public puyoPrintObject
{
    private :
        const int player_num;
        int spawn_spot_state;
        Direction rotate_dir;
    public :
        puyoPrintSpawnspot(int player_num, sf::Sprite screen, POSf pos, int life = puyoImageConstant::PRINT_IMMORTAL);
        void print(sf::RenderWindow &w) override;
};