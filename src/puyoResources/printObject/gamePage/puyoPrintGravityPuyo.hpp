#pragma once

#include "../puyoPrintObject.hpp"
#include "../../../puyoPage/gamePage/puyoTempPuyo/puyoGravityPuyo.hpp"

class puyoPrintGravityPuyo : public puyoPrintObject
{
    private :
        vector<puyoGravityPuyo>& gravity_puyos;
    public :
        puyoPrintGravityPuyo(vector<puyoGravityPuyo>& gp, Sprite puyo, int x, int y, int life);
        void print_object(RenderWindow& w);
};