#pragma once

#include <functional>
#include <memory>

#include "puyoAction/puyoPuyoGravity_temp.hpp"
#include "puyoTempPuyo.hpp"


using namespace std;

class puyoBoard;

class puyoGravityPuyo : public puyoTempPuyo
{
    private :
        unique_ptr<puyoPuyoGravity_temp> gravity;
    public :
        puyoGravityPuyo(float xx, float yy, int c, int amount);

        void gravity_let(puyoBoard& board);
        bool gravity_stopped();
};