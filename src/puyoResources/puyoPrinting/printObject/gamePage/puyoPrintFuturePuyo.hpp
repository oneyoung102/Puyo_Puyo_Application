#pragma once

#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"

#include <vector>

class puyoPrintFuturePuyo : public puyoPrintObject
{
    private :
        const std::vector<puyoPuyo>& future_puyos;
    public :
        puyoPrintFuturePuyo(const std::vector<puyoPuyo>& future_puyos, sf::Sprite puyo, std::pair<int,int> pos, int life);
        void print(sf::RenderWindow& w);
};