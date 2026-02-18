#pragma once

#include "../puyoPrintObject.hpp"

class puyoPrintScreenbar : public puyoPrintObject
{
    private :
        int player_count;
    public :
        puyoPrintScreenbar(int pc, Sprite screen, int x, int y, int life);
        void print_object(RenderWindow& w);
};