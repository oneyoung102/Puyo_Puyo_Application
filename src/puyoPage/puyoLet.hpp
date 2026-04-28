#pragma once

#include <SFML/Graphics.hpp>

#include <optional>
#include <functional>
#include <vector>

class puyoLet
{
    private :
        std::vector<std::function<void()>> key_allot;
    public :
        puyoLet();
        void act_keyboard_let(const std::optional<sf::Event>& event);
        void allot_key(sf::Keyboard::Key key, std::function<void()> func);
        void clear();
};
#define FUNCFY(x) [this](){return x();}