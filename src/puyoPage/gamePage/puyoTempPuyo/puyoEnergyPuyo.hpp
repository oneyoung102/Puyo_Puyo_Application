#pragma once

#include <memory>

#include "puyoAction/puyoPuyoFly_temp.hpp"
#include "puyoTempPuyo.hpp"


using namespace std;

class puyoBoard;

class puyoEnergyPuyo : public puyoTempPuyo
{
    private :
        unique_ptr<puyoPuyoFly_temp> fly;
    public :
        puyoEnergyPuyo(float xx, float yy, float tx, float ty, int c, int amount);

        void fly_let(puyoBoard& board);
        bool fly_stopped();
};