#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class puyoPrintButton
{
    protected:
        int life;
        sf::Sprite sprite;
        sf::Text text;
        const bool& selected;
        int button_x, button_y;
    public:
        puyoPrintButton(sf::Sprite s, const bool& selected, sf::Vector2f pos, std::string content, sf::Font& font, float scaling, sf::Color color, sf::Text::Style style, int life);
        ~puyoPrintButton() = default;
        bool alive();
        virtual void print(sf::RenderWindow& w);
};
