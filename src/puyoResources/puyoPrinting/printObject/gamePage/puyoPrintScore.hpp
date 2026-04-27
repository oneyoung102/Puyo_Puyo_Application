#pragma once

#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

class puyoPrintScore : public puyoPrintObject
{
    private :
        int player_num, from_score;
        const int& to_score;
        void print_num(sf::RenderWindow& w, int img_x, POSf screen_pos);
    public :
        puyoPrintScore(int player_num, const int& score, sf::Sprite num, POSf pos, int life = puyoImageConstant::PRINT_IMMORTAL);
        void print(sf::RenderWindow& w);
};