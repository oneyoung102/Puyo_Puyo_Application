#pragma once

#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"
#include "puyoPage/pages/gamePage/puyoTempPuyo/puyoEnergyPuyo.hpp"

class puyoPrintEnergyPuyo : public puyoPrintObject
{
    private :
        vector<puyoEnergyPuyo>& energy_puyos;
    public :
        puyoPrintEnergyPuyo(vector<puyoEnergyPuyo>& gp, Sprite puyo, int x, int y, int life);
        void print_object(RenderWindow& w);
};