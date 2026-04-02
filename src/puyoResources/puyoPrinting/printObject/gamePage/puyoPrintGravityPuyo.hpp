#pragma once

#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"
#include "puyoPage/pages/gamePage/puyoTempPuyo/puyoGravityPuyo.hpp"

#include <vector>

class puyoPrintGravityPuyo : public puyoPrintObject
{
    private :
        std::vector<puyoGravityPuyo>& gravity_puyos;
    public :
        puyoPrintGravityPuyo(std::vector<puyoGravityPuyo>& gravity_puyos, sf::Sprite puyo, int x, int y, int life);
        void print_object(sf::RenderWindow& w);
};