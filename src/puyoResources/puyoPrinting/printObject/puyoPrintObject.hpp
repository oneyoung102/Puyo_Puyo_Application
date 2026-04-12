#pragma once

#include "puyoPage/pages/gamePage/puyoPuyo/puyoType.hpp"
#include <SFML/Graphics.hpp>

class puyoPrintObject
{
    protected:
        sf::Sprite sprite;
        float x, y;
        int life;
        void print_sprite(sf::RenderWindow& w, sf::Vector2f screen_pos);
        void print_16x16(sf::RenderWindow& w, std::pair<int,int> img_pos, sf::Vector2f screen_pos);
        void print_puyo(sf::RenderWindow& w, puyoType type, sf::Vector2f screen_pos);
    public:
        puyoPrintObject(sf::Sprite s, std::pair<float,float> pos, int life);
        puyoPrintObject(sf::Sprite s, int life);
        virtual ~puyoPrintObject() = default;
        bool alive();
        virtual void print(sf::RenderWindow& w);
};
