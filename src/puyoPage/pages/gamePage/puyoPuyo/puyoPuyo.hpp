#pragma once

#include <utility>
#include <memory>
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoAction/puyoPuyoAct.hpp"

class puyoBoard;

using PUYO_INFO = std::tuple<float,float,puyoType,int>;

class puyoPuyo
{
    private :
        float x, y;
        puyoType type;
        std::unique_ptr<puyoPuyoAct> act;
    public :
        puyoPuyo(float x, float y, puyoType type, std::unique_ptr<puyoPuyoAct>&& act);
        puyoPuyo(float x, float y, puyoType type);

        void move(float to_x, float to_y);

        std::pair<float,float> const get_pos() const;
        puyoType const get_type() const;

        float const get_state() const;
        int const get_tick() const;

        bool const acting() const;
        bool have_act() const;
        void act_let(puyoBoard& board);
        void set_act(std::unique_ptr<puyoPuyoAct>&& act);
        void set_act();
        void let();   
        
};