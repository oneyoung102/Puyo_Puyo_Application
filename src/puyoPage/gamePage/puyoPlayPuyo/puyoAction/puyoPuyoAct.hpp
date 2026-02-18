#pragma once

class puyoBoard;
class puyoPlayPuyo; 

class puyoPuyoAct
{
    protected :
        float start_x1, start_y1, start_x2, start_y2;
        const int act_count_constant;
        int act_count;

        virtual bool test_act(puyoBoard& board,puyoPlayPuyo& puyo) = 0;
        virtual void arrive(puyoPlayPuyo& puyo, float x1,float y1,float x2,float y2);
    public :
        puyoPuyoAct(int amount);
        virtual ~puyoPuyoAct() = default;
        virtual bool decline_act(puyoBoard& board,puyoPlayPuyo& puyo);
        virtual void act_puyo(puyoPlayPuyo& puyo) = 0;
        bool is_acting();
        virtual void let_act();
        void halt_act();
};