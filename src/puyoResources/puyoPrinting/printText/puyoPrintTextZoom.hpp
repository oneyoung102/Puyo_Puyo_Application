#pragma once

#include <SFML/Graphics.hpp>
#include "puyoPos.hpp"
#include "puyoPrintText.hpp"
#include <string>
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

class puyoPrintTextZoom : public puyoPrintText
{
    protected:
        int size;
        const int cycle, dsize, dcycle;
        int cycle_count;
        bool cycle_back = true;
    public:
        puyoPrintTextZoom(POSf pos, std::string content, int cycle, sf::Font& font, int size,
            sf::Color color = sf::Color::White, sf::Text::Style style = sf::Text::Style::Bold, int life = puyoImageConstant::PRINT_IMMORTAL);
        virtual void print(sf::RenderWindow& w);
};
