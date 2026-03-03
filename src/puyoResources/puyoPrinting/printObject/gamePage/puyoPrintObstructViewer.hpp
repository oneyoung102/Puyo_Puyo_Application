#pragma once

#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"


class puyoPrintObstructViewer : public puyoPrintObject
{
    private :
        int& obstruct_puyo;
        int unit;
    public :
        puyoPrintObstructViewer(int& op, Sprite screen, int x, int y, int life);
        void print_object(RenderWindow& w);
};