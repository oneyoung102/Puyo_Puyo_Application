#pragma once

#include "puyoBoard.hpp"

#include <tuple>
#include <utility>
#include <cmath>
#include <functional>


using namespace std;

class puyoPuyoAct;
class puyoPuyoLeft;
class puyoPuyoRight;
class puyoPuyoUp;
class puyoPuyoDown;
class puyoPuyoDrop;
class puyoPuyoTurn;
class puyoPuyoFall;

class puyoPuyo//플레이어가 움직이는 뿌요
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

    public :
        puyoPuyo(float spawn_x1, float spawn_y1, int c1, int c2);

        void act_let(puyoBoard& board);
        void act_fall(puyoBoard& board);

        void deploy_puyo(puyoBoard& board);

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
};