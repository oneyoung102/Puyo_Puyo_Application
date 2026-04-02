#pragma once

#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoType.hpp"

#include <utility>
#include <vector>

class puyoPrintNextPuyo : public puyoPrintObject
{
    private :
        int player_num;
        const int& new_puyo_count;
        const std::vector<std::pair<puyoType,puyoType>>& new_colors;
    public :
        puyoPrintNextPuyo(int player_num, const int& new_puyo_count, const std::vector<std::pair<puyoType,puyoType>>& new_colors, sf::Sprite puyo, int x, int y, int life);
        void print_object(sf::RenderWindow& w);
};