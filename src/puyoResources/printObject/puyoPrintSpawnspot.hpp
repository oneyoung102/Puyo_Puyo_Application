#pragma once

#include "puyoPrintObject.hpp"

#include <utility>

class puyoPrintSpawnspot : public puyoPrintObject
{
    private :
        int player_num;
        int spawn_spot_state;
        bool spawn_spot_rotate_dir;
    public :
        puyoPrintSpawnspot(int pn, Sprite screen, int x, int y, int life);
        void print_object(RenderWindow& w);
};