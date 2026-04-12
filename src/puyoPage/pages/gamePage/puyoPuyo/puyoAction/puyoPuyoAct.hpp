#pragma once

class puyoBoard;
class puyoPuyo; 

class puyoPuyoAct
{
    protected :
        const int act_count_init;
        int act_count;

        virtual bool test(puyoBoard& board,puyoPuyo& puyo);
        virtual void arrive(puyoPuyo& puyo);
    public :
        puyoPuyoAct(int amount);
        virtual ~puyoPuyoAct() = default;

        virtual bool decline(puyoBoard& board,puyoPuyo& puyo);
        virtual void act(puyoPuyo& puyo) = 0;
              
        bool acting();
        void let();
        void halt();
        float get_state();
        int get_act_count_init();
};