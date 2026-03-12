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
    public:
        puyoPrintButton(sf::Sprite s, const bool& selected_temp, float xx, float yy, std::string content, sf::Font& font, float scaling, sf::Color color, sf::Text::Style style,int l);
        bool is_alive();
        void print_button(sf::RenderWindow& w);
};
