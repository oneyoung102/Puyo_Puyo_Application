#pragma once


class puyoBoard;
class puyoTempPuyo; 

class puyoPuyoGravity
{
    private :
        int gravity_count_init, gravity_count;
        float dist;
        bool test_gravity(puyoBoard& board, puyoTempPuyo& puyo);
    public :
        puyoPuyoGravity(int amount);
        bool decline_gravity(puyoBoard& board, puyoTempPuyo& puyo);
        void gravity_puyo(puyoTempPuyo& puyo);
        bool is_gravity_ing();
        void let_gravity();
        void halt_gravity();
};