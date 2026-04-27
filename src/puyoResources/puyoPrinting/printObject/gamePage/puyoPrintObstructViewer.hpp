#pragma once

#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"


class puyoPrintObstructViewer : public puyoPrintObject
{
    private :
        const int& obstruct_puyo;
    public :
        puyoPrintObstructViewer(const int& obstruct_puyo, sf::Sprite screen, POSf pos, int life = puyoImageConstant::PRINT_IMMORTAL);
        void print(sf::RenderWindow& w);
};