#pragma once

#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"

class puyoPrintScreenhead : public puyoPrintObject
{
    private :
    public :
        puyoPrintScreenhead(sf::Sprite screen, int x, int y, int life);
        void print_object(sf::RenderWindow& w);
};