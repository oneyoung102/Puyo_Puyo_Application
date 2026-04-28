#pragma once

#include "puyoTool/puyoPos.hpp"
#include "puyoResources/puyoPrinting/printButton/puyoPrintButton.hpp"

#include <SFML/Graphics.hpp>
#include <string>

class puyoPrintDialButton : public puyoPrintButton
{
    private :
        const bool& dial_selected;
    public:
        puyoPrintDialButton(sf::Sprite s, const bool& selected, const bool& dial_selected, POSf pos, const std::string& content, const sf::Font& font,
            float scaling = 1.0, sf::Color color = sf::Color::White, sf::Text::Style style = sf::Text::Style::Bold, int life = puyoImageConstant::PRINT_IMMORTAL);
        void print(sf::RenderWindow& w) override;
};
