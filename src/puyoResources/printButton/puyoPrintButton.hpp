#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class puyoPrintButton
{
    protected:
        int life;
        sf::Sprite unselected_sprite, selected_sprite;
        sf::Text text;
        bool& selected;
    public:
        puyoPrintButton(sf::Sprite uss, sf::Sprite ss, bool& selected_temp, float x, float y, std::string content, sf::Font& font, int size, sf::Color color, sf::Text::Style style,int l);
        bool is_alive();
        void print_button(sf::RenderWindow& w);
};
