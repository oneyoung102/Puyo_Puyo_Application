#pragma once

#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"
#include "puyoPage/pages/gamePage/puyoPlayer/puyoPlayer.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

class puyoPrintPlayPuyo : public puyoPrintObject
{
    private :
        puyoPlayer& player;
    public :
        puyoPrintPlayPuyo(puyoPlayer& player, sf::Sprite puyo, POSf pos, int life = puyoImageConstant::PRINT_IMMORTAL);
        void print(sf::RenderWindow& w);
};