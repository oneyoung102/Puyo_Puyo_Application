#pragma once

#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"

class puyoPrintScreen : public puyoPrintObject
{
    private :
        int player_count;
    public :
        puyoPrintScreen(int pc, sf::Sprite screen, int x, int y, int life);
        void print_object(sf::RenderWindow& w);
};