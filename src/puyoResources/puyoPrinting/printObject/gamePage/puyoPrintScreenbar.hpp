#pragma once

#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"

class puyoPrintScreenbar : public puyoPrintObject
{
    private :
        int player_count;
    public :
        puyoPrintScreenbar(int pc, sf::Sprite screen, int x, int y, int life);
        void print_object(sf::RenderWindow& w);
};