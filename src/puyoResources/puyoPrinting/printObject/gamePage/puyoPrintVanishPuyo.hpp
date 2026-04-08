#pragma once

#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"

#include <vector>

class puyoPrintVanishPuyo : public puyoPrintObject
{
    private :
        std::vector<puyoPuyo>& vanish_puyos;
    public :
        puyoPrintVanishPuyo(std::vector<puyoPuyo>& vanish_puyos, sf::Sprite puyo, int x, int y, int life);
        void print(sf::RenderWindow& w);
};