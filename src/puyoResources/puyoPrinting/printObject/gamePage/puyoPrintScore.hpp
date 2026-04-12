#pragma once

#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"

class puyoPrintScore : public puyoPrintObject
{
    private :
        int player_num, from_score;
        const int& to_score;
        void print_num(sf::RenderWindow& w, int img_x, sf::Vector2f screen_pos);
    public :
        puyoPrintScore(int player_num, const int& score, sf::Sprite num, std::pair<int,int> pos, int life);
        void print(sf::RenderWindow& w);
};