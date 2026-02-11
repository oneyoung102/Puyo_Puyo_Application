#pragma once

#include <tuple>
#include <utility>
#include <cmath>
#include <functional>

#include "puyoPhase/puyoTempPuyo.hpp"


using namespace std;

class puyoPuyoAct;
class puyoPuyoLeft;
class puyoPuyoRight;
class puyoPuyoUp;
class puyoPuyoDown;
class puyoPuyoDrop;
class puyoPuyoTurn;
class puyoPuyoFall;
class puyoPuyoStay;

class puyoBoard;

struct future_puyo
{
    int x, y, color;
};

class puyoPlayPuyo//플레이어가 움직이는 뿌요
{
    private :
        float x1, y1, x2, y2; // 1이 중심 뿌요
        int color1, color2;

        vector<puyoPuyoAct*> acts;
        puyoPuyoLeft* left;
        puyoPuyoRight* right;
        puyoPuyoUp* up;
        puyoPuyoDown* down;
        puyoPuyoDrop* drop;
        puyoPuyoTurn* turn;
        puyoPuyoFall* fall;

        puyoPuyoAct* action; //명령이 들어온 행동
        puyoPuyoStay* stay;

    public :
        puyoPlayPuyo(pair<float,float> spawn_pos, pair<int,int> color);

        bool act_let(puyoBoard& board);
        bool act_fall(puyoBoard& board);
        bool is_holding();

        vector<puyoTempPuyo> to_temp_puyo();

        bool puyo_touched(puyoBoard& board, int ix, int iy);

        tuple<float,float,float,float> get_puyo_pos();
        void move_puyo(float to_x1, float to_y1, float to_x2, float to_y2);
        pair<int,int> get_puyo_color();
        
        function<void()> get_let_left();
        function<void()> get_let_right();
        function<void()> get_let_down();
        //function<void()> get_let_up();
        function<void()> get_let_turn();
        function<void()> get_let_drop();

        vector<future_puyo> get_future_puyo(puyoBoard& board); 
};