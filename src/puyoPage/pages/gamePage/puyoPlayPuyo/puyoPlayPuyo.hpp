#pragma once

#include <utility>
#include <memory>
#include <vector>

#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"

#include "puyoPage/pages/gamePage/puyoPuyo/puyoAction/puyoPuyoAct.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoAction/puyoPuyoGravity.hpp"
#include "puyoPage/puyoObjectSignal/puyoObjectSignal.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/puyoType.hpp"
#include "puyoTool/puyoPos.hpp"
#include "puyoTool/puyoDir.hpp"


class puyoPuyoGravity;
class puyoPuyoStay;
class puyoBoard;

enum class puyoPlayPuyoSignal
{
    puyo_move,
    COUNT
};

using PLAYPUYO = std::array<puyoPuyo,2>;

class puyoPlayPuyo : public puyoObjectSignal<puyoPlayPuyoSignal>//플레이어가 움직이는 뿌요
{
    private :
        int stay;
        const int gravity_value, stay_value;
        PLAYPUYO play_puyo;
        std::array<std::unique_ptr<puyoPuyoAct>,2> gravity;
        
        bool down_taken, drop_taken;//명령 접수 여부

        void let_fourway(Direction dir);
        void arrive();
    public :
        puyoPlayPuyo(PLAYPUYO&& play_puyo, int gravity_value, int stay_value);

        void act_let(const puyoBoard& board);
        void gravity_let(const puyoBoard& board);
        
        bool down() const;
        bool dropped() const;

        std::vector<puyoPuyo> to_gravity_puyo(const puyoBoard& board);
        const puyoPuyo& view_each(size_t number) const;
        const PLAYPUYO& view() const;
        std::pair<POSf,POSf> get_pos() const;
        std::pair<puyoType::Type,puyoType::Type> get_type() const;

        bool sat(const puyoBoard& board) const; 
        bool moving() const;
        
        void let_left();
        void let_right();
        void let_down();
        void let_up();
        void let_turn();
        void let_drop();
};