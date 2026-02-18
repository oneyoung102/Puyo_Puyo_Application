#pragma once

#include <SFML/Graphics.hpp>
#include "puyoPrintText.hpp"
#include <string>

class puyoPrintTextZoom : public puyoPrintText
{
    protected:
        int cycle, cycle_count;
        bool cycle_back = true;
        int size, dsize, dcycle ;
    public:
        puyoPrintTextZoom(float x, float y, std::string content, sf::Font& font, int size, sf::Color color, sf::Text::Style style, int l, int c);
        virtual void print_text(sf::RenderWindow& w);
};
