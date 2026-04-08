#pragma once

#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"

class puyoPrintScore : public puyoPrintObject
{
    private :
        int player_num, from_score;
        const int& to_score;
        void print_num(sf::RenderWindow& w, int img_x,int px, int py);
    public :
        puyoPrintScore(int player_num, const int& score, sf::Sprite num, int x, int y, int life);
        void print(sf::RenderWindow& w);
};