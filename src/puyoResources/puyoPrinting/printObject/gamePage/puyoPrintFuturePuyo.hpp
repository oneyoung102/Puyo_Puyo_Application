#pragma once

#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

#include <vector>

class puyoPrintFuturePuyo : public puyoPrintObject
{
    private :
        const std::vector<puyoPuyo>& future_puyos;
    public :
        puyoPrintFuturePuyo(const std::vector<puyoPuyo>& future_puyos, sf::Sprite puyo, POSf pos, int life = puyoImageConstant::PRINT_IMMORTAL);
        void print(sf::RenderWindow& w);
};