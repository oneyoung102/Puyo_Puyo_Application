#pragma once

#include "puyoPuyoAct.hpp"
#include <memory>


class puyoBoard;
class puyoPlayPuyo; 

class puyoPuyoTurn : public puyoPuyoAct
{
    private :
        std::unique_ptr<puyoPuyoAct> sub_act;
        float degree;
        bool test(puyoBoard& board, puyoPlayPuyo& puyo) override;
        void arrive(puyoPlayPuyo& puyo, float x1,float y1,float x2,float y2) override;
    public :
        puyoPuyoTurn(int amount, float degree);
        bool decline(puyoBoard& board,puyoPlayPuyo& puyo) override;
        void act(puyoPlayPuyo& puyo) override;
        void let() override;
};