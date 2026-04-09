#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class puyoPrintText
{
    protected:
        int life;
        sf::Text text;

    public:
        puyoPrintText(double x, double y, std::string content, sf::Font& font, int size, sf::Color color, sf::Text::Style style, int life);
        virtual ~puyoPrintText() = default;
        bool alive();
        virtual void print(sf::RenderWindow& w);
};
