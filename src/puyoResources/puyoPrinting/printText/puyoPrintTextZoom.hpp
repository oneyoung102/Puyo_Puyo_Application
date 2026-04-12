#pragma once

#include <SFML/Graphics.hpp>
#include "puyoPrintText.hpp"
#include <string>

class puyoPrintTextZoom : public puyoPrintText
{
    protected:
        int size;
        const int cycle, dsize, dcycle;
        int cycle_count;
        bool cycle_back = true;
    public:
        puyoPrintTextZoom(sf::Vector2f pos, std::string content, sf::Font& font, int size, sf::Color color, sf::Text::Style style, int life, int cycle);
        virtual void print(sf::RenderWindow& w);
};
