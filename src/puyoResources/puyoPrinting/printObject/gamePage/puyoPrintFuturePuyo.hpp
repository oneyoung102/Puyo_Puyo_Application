#pragma once

#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"
#include "puyoPage/pages/gamePage/puyoTempPuyo/puyoFuturePuyo.hpp"

#include <vector>

class puyoPrintFuturePuyo : public puyoPrintObject
{
    private :
        std::vector<puyoFuturePuyo>& future_puyos;
    public :
        puyoPrintFuturePuyo(std::vector<puyoFuturePuyo>& future_puyos, sf::Sprite puyo, int x, int y, int life);
        void print_object(sf::RenderWindow& w);
};