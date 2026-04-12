#pragma once

#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"

#include <vector>

class puyoPrintGravityPuyo : public puyoPrintObject
{
    private :
        const std::vector<puyoPuyo>& gravity_puyos;
    public :
        puyoPrintGravityPuyo(const std::vector<puyoPuyo>& gravity_puyos, sf::Sprite puyo, std::pair<int,int> pos, int life);
        void print(sf::RenderWindow& w);
};