#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "puyoPos.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

class puyoPrintText
{
    protected:
        int life;
        sf::Text text;
    public:
        puyoPrintText(POSf pos, std::string content, sf::Font& font, int size,
            sf::Color color = sf::Color::White, sf::Text::Style style = sf::Text::Style::Bold, int life = puyoImageConstant::PRINT_IMMORTAL);
        virtual ~puyoPrintText() = default;
        bool alive();
        virtual void print(sf::RenderWindow& w);
};
