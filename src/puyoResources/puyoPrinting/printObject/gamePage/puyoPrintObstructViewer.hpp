#pragma once

#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"


class puyoPrintObstructViewer : public puyoPrintObject
{
    private :
        const int& obstruct_puyo;
    public :
        puyoPrintObstructViewer(const int& obstruct_puyo, sf::Sprite screen, std::pair<int,int> pos, int life);
        void print(sf::RenderWindow& w);
};