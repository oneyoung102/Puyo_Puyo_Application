#pragma once

class puyoBoard;
class puyoPuyo; 

class puyoPuyoAct_temp
{
    protected :
        const int act_count_init;
        int act_count;

        virtual bool test(puyoBoard& board,puyoPuyo& puyo) = 0;
    public :
        puyoPuyoAct_temp(int amount);
        virtual ~puyoPuyoAct_temp() = default;

        virtual bool decline(puyoBoard& board,puyoPuyo& puyo) = 0;
        virtual void act(puyoPuyo& puyo) = 0;
        
        bool acting();
        virtual void let();
        void halt();
        float get_state();
        int get_act_count_init();
};