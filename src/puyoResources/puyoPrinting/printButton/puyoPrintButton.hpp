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
        puyoPrintButton(sf::Sprite s, const bool& selected, float xx, float yy, std::string content, sf::Font& font, float scaling, sf::Color color, sf::Text::Style style, int life);
        ~puyoPrintButton() = default;
        bool is_alive();
        virtual void print_button(sf::RenderWindow& w);
};
