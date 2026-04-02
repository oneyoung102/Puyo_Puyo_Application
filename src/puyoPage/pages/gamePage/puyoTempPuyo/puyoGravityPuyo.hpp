#pragma once

#include <memory>

#include "puyoAction/puyoPuyoGravity_temp.hpp"
#include "puyoPage/pages/gamePage/puyoTempPuyo/puyoTempPuyo.hpp"

class puyoBoard;

class puyoGravityPuyo : public puyoTempPuyo
{
    private :
        std::unique_ptr<puyoPuyoGravity_temp> gravity;
    public :
        puyoGravityPuyo(float x, float y, puyoType type, int amount);

        bool deploy_puyo(puyoBoard& board);
        void gravity_let(puyoBoard& board);
        bool gravity_stopped();
        bool is_fast();
};