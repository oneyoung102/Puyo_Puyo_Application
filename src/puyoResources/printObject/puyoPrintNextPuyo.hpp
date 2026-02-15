#pragma once

#include "puyoPrintObject.hpp"
#include "../../puyoPhase/puyoPhasing.hpp"

#include <utility>

class puyoPrintNextPuyo : public puyoPrintObject
{
    private :
        int player_num;
        int& new_puyo_count;
        vector<pair<int,int>>& new_colors;
        void print_puyo(RenderWindow& w,int img_x, int img_y,int px, int py);
    public :
        puyoPrintNextPuyo(int pn, int& npc, vector<pair<int,int>>& nc, Sprite puyo, int x, int y, int life);
        void print_object(RenderWindow& w);
};