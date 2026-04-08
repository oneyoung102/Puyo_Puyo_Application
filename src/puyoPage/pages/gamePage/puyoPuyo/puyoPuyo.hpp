#pragma once

#include <utility>
#include <memory>
#include "puyoPage/pages/gamePage/puyoBoard/puyoType.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoAction/puyoPuyoAct_temp.hpp"

class puyoBoard;

using PUYO_INFO = std::tuple<float,float,puyoType,int>;

class puyoPuyo
{
    private :
        float x, y;
        puyoType type;
        std::unique_ptr<puyoPuyoAct_temp> act;
    public :
        puyoPuyo(float x, float y, puyoType type, std::unique_ptr<puyoPuyoAct_temp>&& act);
        puyoPuyo(float x, float y, puyoType type);

        bool touched(puyoBoard& board, int ix, int iy);
        void move(float to_x, float to_y);

        std::pair<float,float> get_pos();
        puyoType get_type();
        int get_tick();

        bool acting();
        float get_state();
        void act_let(puyoBoard& board);
        void change_act(std::unique_ptr<puyoPuyoAct_temp>&& act);
        void let();   
        
};