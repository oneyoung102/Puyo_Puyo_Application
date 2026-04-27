#pragma once

#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"

class puyoPrintScreen : public puyoPrintObject
{
    public :
        puyoPrintScreen(int player_count, sf::Sprite screen, int life = puyoImageConstant::PRINT_IMMORTAL);
};