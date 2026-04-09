#pragma once

#include "puyoResources/puyoPrinting/printButton/puyoPrintButton.hpp"

#include <SFML/Graphics.hpp>
#include <string>

class puyoPrintDialButton : public puyoPrintButton
{
    private :
        const bool& dial_selected;
    public:
        puyoPrintDialButton(sf::Sprite s, const bool& selected, const bool& dial_selected, double x, double y, std::string content, sf::Font& font, double scaling, sf::Color color, sf::Text::Style style, int life);
        void print(sf::RenderWindow& w) override;
};
