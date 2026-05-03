#pragma once

#include "puyoPage/pages/gamePage/puyoPuyo/puyoType.hpp"
#include "puyoTool/puyoPos.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"
#include <SFML/Graphics.hpp>

class puyoPrintObject
{
    protected:
        sf::Sprite sprite;
        POSf pos;
        int life;
        void print_sprite(sf::RenderWindow& w, POSf screen_pos);
        void print_16x16(sf::RenderWindow& w, POSi img_pos, POSf screen_pos);
        void print_puyo(sf::RenderWindow& w, puyoType type, POSf screen_pos);
    public:
        puyoPrintObject(sf::Sprite s, POSf pos, int life = puyoImageConstant::PRINT_IMMORTAL);
        puyoPrintObject(sf::Sprite s, int life = puyoImageConstant::PRINT_IMMORTAL);
        virtual ~puyoPrintObject() = default;
        bool alive();
        bool is_immortal();
        virtual void print(sf::RenderWindow& w);
};
