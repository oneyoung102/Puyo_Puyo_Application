#pragma once

#include <SFML/Graphics.hpp>
#include "puyoTool/puyoPos.hpp"
#include "puyoPrintText.hpp"
#include <string>
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

class puyoPrintTextZoom : public puyoPrintText
{
    protected:
        int size;
        const int cycle, dsize, dcycle;
        int cycle_count;
        bool size_bigger;
    public:
        puyoPrintTextZoom(POSf pos, const std::string& content, const sf::Font& font, int size, int cycle,
            sf::Color color = sf::Color::White, sf::Text::Style style = sf::Text::Style::Bold, int life = puyoImageConstant::PRINT_IMMORTAL);
        virtual void print(sf::RenderWindow& w);
};
