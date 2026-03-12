#pragma once

#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"
#include "puyoPage/pages/gamePage/puyoTempPuyo/puyoVanishPuyo.hpp"

#include <vector>

class puyoPrintVanishPuyo : public puyoPrintObject
{
    private :
        std::vector<puyoVanishPuyo>& vanish_puyos;
    public :
        puyoPrintVanishPuyo(std::vector<puyoVanishPuyo>& vp, sf::Sprite puyo, int x, int y, int life);
        void print_object(sf::RenderWindow& w);
};