#pragma once

#include "puyoPuyoAct.hpp"
#include <utility>

class puyoBoard;
class puyoPuyo; 

class puyoPuyoFly : public puyoPuyoAct
{
    private :
        const float from_x, from_y, to_x, to_y;
        void arrive(puyoPuyo& puyo) override;
    public :
        puyoPuyoFly(std::pair<float,float> from_pos,std::pair<float,float> to_pos,int amount);
        void act(puyoPuyo& puyo) override;
};