#pragma once

#include <SFML/Graphics.hpp>
#include "puyoPos.hpp"
#include "puyoPrintText.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"
#include <string>

class puyoPrintTextFlash : public puyoPrintText
{
    private:
        const int cycle;//옵션 주기
        int cycle_count;
        bool cycle_back;
    public:
        puyoPrintTextFlash(POSf pos, std::string content, int cycle, sf::Font& font, int size,
            sf::Color color = sf::Color::White, sf::Text::Style style = sf::Text::Style::Bold, int life = puyoImageConstant::PRINT_IMMORTAL);
        void print(sf::RenderWindow& w);
};
