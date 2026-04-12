#pragma once

#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"

class puyoPrintScreen : public puyoPrintObject
{
    private :
        int player_count;
    public :
        puyoPrintScreen(int player_count, sf::Sprite screen, int life);
};