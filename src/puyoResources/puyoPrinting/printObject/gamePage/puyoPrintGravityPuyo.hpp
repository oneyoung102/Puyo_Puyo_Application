#pragma once

#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"

#include <vector>

class puyoPrintGravityPuyo : public puyoPrintObject
{
    private :
        std::vector<puyoPuyo>& gravity_puyos;
    public :
        puyoPrintGravityPuyo(std::vector<puyoPuyo>& gravity_puyos, sf::Sprite puyo, int x, int y, int life);
        void print(sf::RenderWindow& w);
};