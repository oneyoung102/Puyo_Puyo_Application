#pragma once

#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/puyoType.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

#include <utility>
#include <vector>

class puyoPrintNextPuyo : public puyoPrintObject
{
    private :
        int player_num;
        const int& new_puyo_count;
        const std::vector<std::pair<puyoType,puyoType>>& new_types;
    public :
        puyoPrintNextPuyo(int player_num, const int& new_puyo_count, const std::vector<std::pair<puyoType,puyoType>>& new_types, sf::Sprite puyo, POSf pos, int life = puyoImageConstant::PRINT_IMMORTAL);
        void print(sf::RenderWindow& w);
};