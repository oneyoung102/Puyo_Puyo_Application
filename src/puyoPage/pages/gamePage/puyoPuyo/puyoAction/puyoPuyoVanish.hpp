#pragma once

#include "puyoPuyoAct.hpp"

class puyoBoard;
class puyoPuyo; 

class puyoPuyoVanish : public puyoPuyoAct
{
    private :
        float dist;
    public :
        puyoPuyoVanish(int amount);
        std::unique_ptr<puyoPuyoAct> clone() const override;
        void act(puyoPuyo& puyo) override;
};