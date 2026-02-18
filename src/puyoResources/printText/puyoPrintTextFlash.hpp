#pragma once

#include <SFML/Graphics.hpp>
#include "puyoPrintText.hpp"
#include <string>

class puyoPrintTextFlash : public puyoPrintText
{
    private:
        int cycle, cycle_count;//옵션 주기
        bool cycle_back;
    public:
        puyoPrintTextFlash(float x, float y, std::string content, sf::Font& font, int size, sf::Color color, sf::Text::Style style, int l, int c);
        void print_text(sf::RenderWindow& w);
};
