#pragma once

#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

#include <vector>

class puyoPrintEnergyPuyo : public puyoPrintObject
{
    private :
        const std::vector<puyoPuyo>& energy_puyos;
    public :
        puyoPrintEnergyPuyo(const std::vector<puyoPuyo>& energy_puyos, sf::Sprite puyo, int life = puyoImageConstant::PRINT_IMMORTAL);
        void print(sf::RenderWindow& w);
};