#pragma once

#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

class puyoPrintScreenhead : public puyoPrintObject
{
    private :
    public :
        puyoPrintScreenhead(sf::Sprite screen, int life = puyoImageConstant::PRINT_IMMORTAL);
};