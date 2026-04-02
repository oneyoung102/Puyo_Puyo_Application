#pragma once

#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"
#include "puyoPage/pages/gamePage/puyoTempPuyo/puyoEnergyPuyo.hpp"

#include <vector>

class puyoPrintEnergyPuyo : public puyoPrintObject
{
    private :
        std::vector<puyoEnergyPuyo>& energy_puyos;
    public :
        puyoPrintEnergyPuyo(std::vector<puyoEnergyPuyo>& energy_puyos, sf::Sprite puyo, int x, int y, int life);
        void print_object(sf::RenderWindow& w);
};