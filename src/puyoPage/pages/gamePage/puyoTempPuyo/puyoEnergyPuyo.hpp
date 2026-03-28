#pragma once

#include <memory>

#include "puyoAction/puyoPuyoFly_temp.hpp"
#include "puyoPage/pages/gamePage/puyoTempPuyo/puyoTempPuyo.hpp"

class puyoBoard;

class puyoEnergyPuyo : public puyoTempPuyo
{
    private :
        std::unique_ptr<puyoPuyoFly_temp> fly;
    public :
        puyoEnergyPuyo(float xx, float yy, float tx, float ty, puyoType c, int amount);

        void fly_let(puyoBoard& board);
        bool fly_stopped();
};