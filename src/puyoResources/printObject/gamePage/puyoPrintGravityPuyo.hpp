#pragma once

#include "../puyoPrintObject.hpp"
#include "../../../puyoPage/gamePage/puyoTempPuyo/puyoGravityPuyo.hpp"

class puyoPrintGravityPuyo : public puyoPrintObject
{
    private :
        vector<puyoGravityPuyo>& gravity_puyos;
        void print_puyo(RenderWindow& w,int img_x, int img_y, int px, int py);
    public :
        puyoPrintGravityPuyo(vector<puyoGravityPuyo>& gp, Sprite puyo, int x, int y, int life);
        void print_object(RenderWindow& w);
};