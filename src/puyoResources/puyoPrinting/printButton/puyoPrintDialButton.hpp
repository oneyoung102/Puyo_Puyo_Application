#pragma once

#include "puyoResources/puyoPrinting/printButton/puyoPrintButton.hpp"

#include <SFML/Graphics.hpp>
#include <string>

class puyoPrintDialButton : public puyoPrintButton
{
    private :
        const bool& dial_selected;
    public:
        puyoPrintDialButton(sf::Sprite s, const bool& selected_temp, const bool& dial_selected_temp, float xx, float yy, std::string content, sf::Font& font, float scaling, sf::Color color, sf::Text::Style style,int l);
        void print_button(sf::RenderWindow& w) override;
};
