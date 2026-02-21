#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class puyoPrintObject
{
    protected:
        Sprite sprite;
        float x, y;
        int life;
        void print_sprite(RenderWindow& w, float x1, float y1);
    public:
        puyoPrintObject(Sprite s, float xx, float yy, int l);
        virtual ~puyoPrintObject() = default;
        bool is_alive();
        virtual void print_object(RenderWindow& w);
};
