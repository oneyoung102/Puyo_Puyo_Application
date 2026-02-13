#pragma once

#include <tuple>
#include <utility>
#include <cmath>
#include <functional>
#include <memory>

#include "../puyoTempPuyo/puyoGravityPuyo.hpp"
#include "../puyoTempPuyo/puyoFuturePuyo.hpp"

#include "puyoAction/puyoPuyoAct.hpp"
#include "puyoAction/puyoPuyoGravity.hpp"
#include "puyoAction/puyoPuyoStay.hpp"


using namespace std;

class puyoPuyoGravity;
class puyoPuyoStay;


class puyoBoard;

class puyoPlayPuyo//플레이어가 움직이는 뿌요
{
    private :
        enum class Act_num
        {
            left,
            right,
            down,
            turn,
            drop
        };
        float x1, y1, x2, y2; // 1이 중심 뿌요
        int color1, color2;

        unique_ptr<puyoPuyoGravity> gravity;
        unique_ptr<puyoPuyoStay> stay;
        vector<shared_ptr<puyoPuyoAct>> acts;

        shared_ptr<puyoPuyoAct> action; //명령이 들어온 행동
        

        int gravity_value;

    public :
        puyoPlayPuyo(pair<float,float> spawn_pos, pair<int,int> color, int g);

        void act_let(puyoBoard& board);
        void gravity_let(puyoBoard& board);
        bool is_dropped();
        bool is_holding();

        vector<puyoGravityPuyo> to_gravity_puyo();

        bool puyo_touched(puyoBoard& board, int ix, int iy);

        tuple<float,float,float,float> get_puyo_pos();
        void move_puyo(float to_x1, float to_y1, float to_x2, float to_y2);
        pair<int,int> get_puyo_color();
        
        void let_left();
        void let_right();
        void let_down();
        void let_up();
        void let_turn();
        void let_drop();

        vector<puyoFuturePuyo> get_future_puyo(puyoBoard& board); 
};