#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class puyoPrintText
{
    protected:
        int life;
        sf::Text text;

    public:
        puyoPrintText(float x, float y, std::string content, sf::Font& font, int size, sf::Color color, sf::Text::Style style,int l);
        virtual ~puyoPrintText() = default;
        bool is_alive();
        virtual void print_text(sf::RenderWindow& w);
};
