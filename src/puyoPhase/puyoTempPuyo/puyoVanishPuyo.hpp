#pragma once

#include <memory>

#include "puyoAction/puyoPuyoVanish_temp.hpp"
#include "puyoTempPuyo.hpp"


using namespace std;

class puyoBoard;

class puyoVanishPuyo : public puyoTempPuyo
{
    private :
        float x, y;
        int color;
        unique_ptr<puyoPuyoVanish_temp> vanish;
    public :
        puyoVanishPuyo(float xx, float yy, int c, int amount);

        bool vanish_stopped();

        void vanish_let(puyoBoard& board);
        bool vanish_soon();
};