#pragma once

#include "puyoPrintObject.hpp"
#include "../../puyoPhase/puyoPlayPuyo/puyoPlayPuyo.hpp"

class puyoPrintPlayPuyo : public puyoPrintObject
{
    private :
        puyoPlayPuyo& play_puyo;
        void print_puyo(RenderWindow& w,int img_x, int img_y, int px, int py);
    public :
        puyoPrintPlayPuyo(puyoPlayPuyo& pp, Sprite puyo, int x, int y, int life);
        void print_object(RenderWindow& w);
};