#pragma once

#include <utility>
#include <memory>
#include "puyoPage/pages/gamePage/puyoBoard/puyoType.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoAction/puyoPuyoAct.hpp"

class puyoBoard;

using PUYO_INFO = std::tuple<double,double,puyoType,int>;

class puyoPuyo
{
    private :
        double x, y;
        puyoType type;
        std::unique_ptr<puyoPuyoAct> act;
    public :
        puyoPuyo(double x, double y, puyoType type, std::unique_ptr<puyoPuyoAct>&& act);
        puyoPuyo(double x, double y, puyoType type);

        void move(double to_x, double to_y);

        std::pair<double,double> const get_pos() const;
        puyoType const get_type() const;

        double const get_state() const;
        int const get_tick() const;

        bool const acting() const;
        bool have_act() const;
        void act_let(puyoBoard& board);
        void set_act(std::unique_ptr<puyoPuyoAct>&& act);
        void set_act();
        void let();   
        
};