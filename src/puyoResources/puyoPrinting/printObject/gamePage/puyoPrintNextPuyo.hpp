#pragma once

#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"

#include <utility>
#include <vector>

class puyoPrintNextPuyo : public puyoPrintObject
{
    private :
        int player_num;
        const int& new_puyo_count;
        const std::vector<std::pair<int,int>>& new_colors;
    public :
        puyoPrintNextPuyo(int pn, const int& npc, const std::vector<std::pair<int,int>>& nc, sf::Sprite puyo, int x, int y, int life);
        void print_object(sf::RenderWindow& w);
};