#pragma once

#include <SFML/Graphics.hpp>
#include "puyoPrintText.hpp"
#include <string>

class puyoPrintTextFlash : public puyoPrintText
{
    private:
        const int cycle;//옵션 주기
        int cycle_count;
        bool cycle_back;
    public:
        puyoPrintTextFlash(double x, double y, std::string content, sf::Font& font, int size, sf::Color color, sf::Text::Style style, int life, int cycle);
        void print(sf::RenderWindow& w);
};
