#pragma once

#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

class puyoPrintScreenbar : public puyoPrintObject
{
    public :
        puyoPrintScreenbar(int player_count, sf::Sprite screen, int life = puyoImageConstant::PRINT_IMMORTAL);
};