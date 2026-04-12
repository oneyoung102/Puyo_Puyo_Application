#pragma once

#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"
#include "puyoPage/pages/gamePage/puyoPlayer/puyoPlayer.hpp"

class puyoPrintPlayPuyo : public puyoPrintObject
{
    private :
        puyoPlayer& player;
    public :
        puyoPrintPlayPuyo(puyoPlayer& player, sf::Sprite puyo, std::pair<int,int> pos, int life);
        void print(sf::RenderWindow& w);
};