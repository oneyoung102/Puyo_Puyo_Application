#pragma once

#include "puyoPrintObject.hpp"

class puyoPrintScreen : public puyoPrintObject
{
    private :
        int player_count;
    public :
        puyoPrintScreen(int pc, Sprite screen, int x, int y, int life);
        void print_object(RenderWindow& w);
};