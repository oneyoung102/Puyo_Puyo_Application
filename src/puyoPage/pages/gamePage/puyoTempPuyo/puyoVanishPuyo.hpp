#pragma once

#include <memory>

#include "puyoAction/puyoPuyoVanish_temp.hpp"
#include "puyoPage/pages/gamePage/puyoTempPuyo/puyoTempPuyo.hpp"

class puyoBoard;

class puyoVanishPuyo : public puyoTempPuyo
{
    private :
        float x, y;
        int color;
        std::unique_ptr<puyoPuyoVanish_temp> vanish;
    public :
        puyoVanishPuyo(float xx, float yy, int c, int amount);

        bool vanish_stopped();

        void vanish_let(puyoBoard& board);
        bool vanish_soon();
        bool vanish_stay();
};