#pragma once

#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"
#include "puyoPage/pages/gamePage/puyoTempPuyo/puyoFuturePuyo.hpp"

class puyoPrintFuturePuyo : public puyoPrintObject
{
    private :
        vector<puyoFuturePuyo>& future_puyos;
    public :
        puyoPrintFuturePuyo(vector<puyoFuturePuyo>& fp, Sprite puyo, int x, int y, int life);
        void print_object(RenderWindow& w);
};