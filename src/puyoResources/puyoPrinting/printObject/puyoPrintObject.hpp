#pragma once

#include <SFML/Graphics.hpp>

class puyoPrintObject
{
    protected:
        sf::Sprite sprite;
        float x, y;
        int life;
        void print_sprite(sf::RenderWindow& w, float x1, float y1);
        void print_puyo(sf::RenderWindow& w, int img_x, int img_y, int px, int py);
    public:
        puyoPrintObject(sf::Sprite s, float xx, float yy, int l);
        virtual ~puyoPrintObject() = default;
        bool is_alive();
        virtual void print_object(sf::RenderWindow& w);
};
