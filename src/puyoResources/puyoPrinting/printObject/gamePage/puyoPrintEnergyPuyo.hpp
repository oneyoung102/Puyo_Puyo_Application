#pragma once

#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"

#include <vector>

class puyoPrintEnergyPuyo : public puyoPrintObject
{
    private :
        std::vector<puyoPuyo>& energy_puyos;
    public :
        puyoPrintEnergyPuyo(std::vector<puyoPuyo>& energy_puyos, sf::Sprite puyo, int x, int y, int life);
        void print(sf::RenderWindow& w);
};