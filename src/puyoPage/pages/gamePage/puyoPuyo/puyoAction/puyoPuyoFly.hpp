#pragma once

#include "puyoPuyoAct.hpp"

class puyoBoard;
class puyoPuyo; 

class puyoPuyoFly : public puyoPuyoAct
{
    private :
        const double from_x, from_y, to_x, to_y;
        void arrive(puyoPuyo& puyo) override;
    public :
        puyoPuyoFly(double fx, double fy, double tx, double ty,int amount);
        void act(puyoPuyo& puyo) override;
};