#pragma once

#include <memory>
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoAction/puyoPuyoAct.hpp"
#include "puyoPos.hpp"

class puyoBoard;

using PUYO_INFO = std::tuple<POS,puyoType,int>; // {POS,TYPE,TICK}

class puyoPuyo
{
    private :
        POS pos;
        puyoType type;
        std::unique_ptr<puyoPuyoAct> act;
    public :
        puyoPuyo(POS pos, puyoType type, std::unique_ptr<puyoPuyoAct>&& act);
        puyoPuyo(POS pos, puyoType type);

        void move(POS to_pos);

        POS const get_pos() const;
        puyoType const get_type() const;

        float const get_state() const;
        int const get_tick() const;

        bool const acting() const;
        bool have_act() const;
        void act_let(const puyoBoard& board);
        void set_act(std::unique_ptr<puyoPuyoAct>&& act);
        void set_act();
        void let();   
        
};