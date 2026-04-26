#pragma once

#include <utility>
#include <memory>

#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"

#include "puyoPage/pages/gamePage/puyoPuyo/puyoAction/puyoPuyoAct.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoAction/puyoPuyoGravity.hpp"
#include "puyoPage/puyoObjectSignal.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType.hpp"


class puyoPuyoGravity;
class puyoPuyoStay;
class puyoBoard;

enum class puyoPlayPuyoSignal
{
    puyo_move,
    COUNT
};

class puyoPlayPuyo : public puyoObjectSignal<puyoPlayPuyoSignal>//플레이어가 움직이는 뿌요
{
    private :
        int stay;
        const int gravity_value, stay_value;
        std::array<std::unique_ptr<puyoPuyo>,2> play_puyo;
        std::array<std::unique_ptr<puyoPuyoAct>,2> gravity;
        
        bool down_taken, drop_taken;//명령 접수 여부

    public :
        puyoPlayPuyo(POS spawn_pos, std::pair<puyoType,puyoType> types, int gravity_value, int stay_value);

        void act_let(puyoBoard& board);
        void gravity_let(puyoBoard& board);
        
        bool down();
        bool dropped(const puyoBoard& board);

        int get_height(const puyoBoard& board);

        std::vector<PUYO_INFO> to_gravity_puyo(const puyoBoard& board) const;
        const std::unique_ptr<puyoPuyo>& get_each(size_t number);
        const decltype(play_puyo)& get();
        std::tuple<float,float,float,float> get_pos() const;
        std::pair<puyoType,puyoType> get_type() const;

        bool sat(const puyoBoard& board) const; 
        bool moving() const;
        
        void let_left();
        void let_right();
        void let_down();
        void let_up();
        void let_turn();
        void let_drop();
};