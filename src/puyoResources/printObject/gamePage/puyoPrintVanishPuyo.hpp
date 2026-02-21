#pragma once

#include "../puyoPrintObject.hpp"
#include "../../../puyoPage/gamePage/puyoTempPuyo/puyoVanishPuyo.hpp"

class puyoPrintVanishPuyo : public puyoPrintObject
{
    private :
        vector<puyoVanishPuyo>& vanish_puyos;
        void print_puyo(RenderWindow& w,int img_x, int img_y, int px, int py);
    public :
        puyoPrintVanishPuyo(vector<puyoVanishPuyo>& vp, Sprite puyo, int x, int y, int life);
        void print_object(RenderWindow& w);
};