#pragma once

#include <tuple>
#include <utility>
#include <memory>

#include "puyoPage/pages/gamePage/puyoTempPuyo/puyoGravityPuyo.hpp"

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
        puyoType color1, color2;

        std::unique_ptr<puyoPuyoGravity> gravity;
        std::unique_ptr<puyoPuyoStay> stay;
        std::vector<std::shared_ptr<puyoPuyoAct>> acts;

        std::shared_ptr<puyoPuyoAct> action; //명령이 들어온 행동
        
        bool taken_down_let;//아래 이동 명령 접수 여부

    public :
        puyoPlayPuyo(std::pair<float,float> spawn_pos, std::pair<puyoType,puyoType> color, int g, int s);

        void act_let(puyoBoard& board);
        void gravity_let(puyoBoard& board);
        bool is_down();
        bool is_dropped();
        bool is_holding();
        int get_drop_height(puyoBoard& board);

        std::vector<puyoGravityPuyo> to_gravity_puyo();

        bool puyo_touched(puyoBoard& board, int ix, int iy);

        std::tuple<float,float,float,float> get_puyo_pos();
        void move_puyo(float to_x1, float to_y1, float to_x2, float to_y2);
        std::pair<puyoType,puyoType> get_puyo_color();
        
        void let_left();
        void let_right();
        void let_down();
        void let_up();
        void let_turn();
        void let_drop();

        bool is_moving();
};