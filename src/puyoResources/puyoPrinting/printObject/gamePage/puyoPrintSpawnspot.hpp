#pragma once

#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"

class puyoPrintSpawnspot : public puyoPrintObject
{
    private :
        const int SPAWN_SPOT_CYCLE;
        int player_num;
        int spawn_spot_state;
        bool spawn_spot_rotate_dir;
    public :
        puyoPrintSpawnspot(int pn, Sprite screen, int x, int y, int life);
        void print_object(RenderWindow& w);
};