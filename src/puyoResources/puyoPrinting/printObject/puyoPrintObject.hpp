#pragma once

#include "puyoPage/pages/gamePage/puyoBoard/puyoType.hpp"
#include <SFML/Graphics.hpp>

class puyoPrintObject
{
    protected:
        sf::Sprite sprite;
        double x, y;
        int life;
        void print_sprite(sf::RenderWindow& w, double x1, double y1);
        void print_16x16(sf::RenderWindow& w, int img_x, int img_y, int px, int py);
        void print_puyo(sf::RenderWindow& w, puyoType type, int px, int py);
    public:
        puyoPrintObject(sf::Sprite s, double x, double y, int life);
        virtual ~puyoPrintObject() = default;
        bool alive();
        virtual void print(sf::RenderWindow& w);
};
