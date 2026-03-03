#pragma once

#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"

#include <utility>
#include <vector>

class puyoPrintNextPuyo : public puyoPrintObject
{
    private :
        int player_num;
        int& new_puyo_count;
        std::vector<std::pair<int,int>>& new_colors;
    public :
        puyoPrintNextPuyo(int pn, int& npc, std::vector<std::pair<int,int>>& nc, Sprite puyo, int x, int y, int life);
        void print_object(RenderWindow& w);
};