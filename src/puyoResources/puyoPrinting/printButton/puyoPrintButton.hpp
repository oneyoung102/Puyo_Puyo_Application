#pragma once

#include "puyoPos.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"
#include <SFML/Graphics.hpp>
#include <string>

class puyoPrintButton
{
    protected:
        int life;
        sf::Sprite sprite;
        sf::Text text;
        const bool& selected;
        POSi img_pos;
    public:
        puyoPrintButton(sf::Sprite s, const bool& selected, POSf pos, std::string content, sf::Font& font,
            float scaling = 1.0, sf::Color color = sf::Color::White, sf::Text::Style style = sf::Text::Style::Bold, int life = puyoImageConstant::PRINT_IMMORTAL);
        ~puyoPrintButton() = default;
        bool alive();
        virtual void print(sf::RenderWindow& w);
};
