#pragma once

#include <tuple>
#include <utility>
#include <memory>

#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"

#include "puyoAction/puyoPuyoAct.hpp"
#include "puyoAction/puyoPuyoGravity.hpp"
#include "puyoAction/puyoPuyoStay.hpp"
#include "puyoPage/puyoObjectSignal.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoType.hpp"


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
        enum class Act_type
        {
            left,
            right,
            down,
            turn,
            drop
        };
        float x1, y1, x2, y2; // 1이 중심 뿌요
        puyoType type1, type2;

        std::unique_ptr<puyoPuyoGravity> gravity;
        std::unique_ptr<puyoPuyoStay> stay;
        std::vector<std::shared_ptr<puyoPuyoAct>> acts;

        std::shared_ptr<puyoPuyoAct> action; //명령이 들어온 행동
        
        bool down_let_is_taken;//아래 이동 명령 접수 여부

    public :
        puyoPlayPuyo(std::pair<float,float> spawn_pos, std::pair<puyoType,puyoType> types, int gravity_value, int stay_value);

        void act_let(puyoBoard& board);
        void gravity_let(puyoBoard& board);
        bool down();
        bool dropped();
        bool holding();
        int get_drop_height(puyoBoard& board);

        std::vector<PUYO_INFO> to_gravity_puyo();

        bool touched(puyoBoard& board, int ix, int iy);

        std::tuple<float,float,float,float> get_pos();
        void move(float to_x1, float to_y1, float to_x2, float to_y2);
        std::pair<puyoType,puyoType> get_types();
        
        void let_left();
        void let_right();
        void let_down();
        void let_up();
        void let_turn();
        void let_drop();

        bool is_moving();
};