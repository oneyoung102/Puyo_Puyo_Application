#pragma once

#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

#include <vector>

class puyoPrintGravityPuyo : public puyoPrintObject
{
    private :
        const std::vector<puyoPuyo>& gravity_puyos;
    public :
        puyoPrintGravityPuyo(const std::vector<puyoPuyo>& gravity_puyos, sf::Sprite puyo, POSf pos, int life = puyoImageConstant::PRINT_IMMORTAL);
        void print(sf::RenderWindow& w);
};