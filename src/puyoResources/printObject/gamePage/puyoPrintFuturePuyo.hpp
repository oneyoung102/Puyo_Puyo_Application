#pragma once

#include "../puyoPrintObject.hpp"
#include "../../../puyoPage/gamePage/puyoTempPuyo/puyoFuturePuyo.hpp"

class puyoPrintFuturePuyo : public puyoPrintObject
{
    private :
        vector<puyoFuturePuyo>& future_puyos;
        void print_puyo(RenderWindow& w,int img_x, int img_y, int px, int py);
    public :
        puyoPrintFuturePuyo(vector<puyoFuturePuyo>& fp, Sprite puyo, int x, int y, int life);
        void print_object(RenderWindow& w);
};