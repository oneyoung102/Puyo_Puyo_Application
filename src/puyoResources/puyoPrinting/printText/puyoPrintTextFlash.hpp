#pragma once

#include <SFML/Graphics.hpp>
#include "puyoTool/puyoPos.hpp"
#include "puyoPrintText.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"
#include <string>

class puyoPrintTextFlash : public puyoPrintText
{
    private:
        const int cycle;//옵션 주기
        int cycle_count;
        bool show;
    public:
        puyoPrintTextFlash(POSf pos, const std::string& content, const sf::Font& font, int size, int cycle, 
            sf::Color color = sf::Color::White, sf::Text::Style style = sf::Text::Style::Bold, int life = puyoImageConstant::PRINT_IMMORTAL);
        void print(sf::RenderWindow& w);
};
