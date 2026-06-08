#pragma once

#include "puyoTool/puyoPos.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"
#include <SFML/Graphics.hpp>

class puyoPrintObject
{
    protected:
        sf::Sprite sprite;
        POSf pos;
        int life;
        void print_sprite(sf::RenderWindow& w, const POSf& screen_pos);
        void print_16x16(sf::RenderWindow& w, const POSi& img_pos, const POSf& screen_pos);
        void print_puyo(sf::RenderWindow& w, const puyoPuyo& puyo, const POSf& screen_pos);
    public:
        puyoPrintObject(sf::Sprite s, const POSf& pos, int life = puyoImageConstant::PRINT_IMMORTAL);
        puyoPrintObject(sf::Sprite s, int life = puyoImageConstant::PRINT_IMMORTAL);
        virtual ~puyoPrintObject() = default;
        bool alive() const;
        bool is_immortal() const;
        virtual void print(sf::RenderWindow& w);
};
