#pragma once

#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"


class puyoPrintObstructViewer : public puyoPrintObject
{
    private :
        const int& obstruct_puyo;
    public :
        puyoPrintObstructViewer(const int& op, sf::Sprite screen, int x, int y, int life);
        void print_object(sf::RenderWindow& w);
};