#pragma once

#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"

class puyoPrintScreenbar : public puyoPrintObject
{
    private :
    public :
        puyoPrintScreenbar(int player_count, sf::Sprite screen, int x, int y, int life);
        void print_object(sf::RenderWindow& w);
};