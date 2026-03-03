#pragma once

#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"
#include "puyoPage/pages/gamePage/puyoTempPuyo/puyoVanishPuyo.hpp"

class puyoPrintVanishPuyo : public puyoPrintObject
{
    private :
        vector<puyoVanishPuyo>& vanish_puyos;
    public :
        puyoPrintVanishPuyo(vector<puyoVanishPuyo>& vp, Sprite puyo, int x, int y, int life);
        void print_object(RenderWindow& w);
};