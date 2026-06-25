#pragma once
#include <memory>

class puyoBoard;
class puyoPuyo; 

class puyoPuyoAct
{
    protected :
        const int act_count_init, __halted;
        int act_count;

        virtual bool test(const puyoBoard& board, puyoPuyo& puyo);
        virtual void arrive(puyoPuyo& puyo);
    public :
        puyoPuyoAct(int amount);
        virtual std::unique_ptr<puyoPuyoAct> clone() const = 0;
        virtual ~puyoPuyoAct() = default;

        virtual bool decide(const puyoBoard& board,puyoPuyo& puyo);
        virtual void act(puyoPuyo& puyo) = 0;
              
        bool acting() const;
        bool halted() const;
        void let(int amount = 0);
        void halt();
        float get_state() const;
        int get_act_count_init() const;
};