#pragma once

#include "../puyoPrintObject.hpp"
#include "../../../puyoPage/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"

class puyoPrintPlayPuyo : public puyoPrintObject
{
    private :
        puyoPlayPuyo& play_puyo;
    public :
        puyoPrintPlayPuyo(puyoPlayPuyo& pp, Sprite puyo, int x, int y, int life);
        void print_object(RenderWindow& w);
};