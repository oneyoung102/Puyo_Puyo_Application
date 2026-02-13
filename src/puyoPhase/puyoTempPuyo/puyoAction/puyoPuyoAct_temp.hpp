#pragma once

class puyoBoard;
class puyoTempPuyo; 

class puyoPuyoAct_temp
{
    protected :
        const int act_count_init;
        int act_count;

        virtual bool test_act(puyoBoard& board,puyoTempPuyo& puyo) = 0;
    public :
        puyoPuyoAct_temp(int amount);
        virtual ~puyoPuyoAct_temp() = default;
        virtual bool decline_act(puyoBoard& board,puyoTempPuyo& puyo) = 0;
        virtual void act_puyo(puyoTempPuyo& puyo) = 0;
        bool is_acting();
        virtual void let_act();
        void halt_act();
        float get_state();
};