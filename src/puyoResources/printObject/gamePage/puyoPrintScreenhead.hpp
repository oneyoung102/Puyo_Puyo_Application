#pragma once

#include "../puyoPrintObject.hpp"

class puyoPrintScreenhead : public puyoPrintObject
{
    private :
    public :
        puyoPrintScreenhead(Sprite screen, int x, int y, int life);
        void print_object(RenderWindow& w);
};