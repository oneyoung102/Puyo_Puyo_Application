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
        void allot_key(int key, std::function<void()> func);
        void clear_allot();
};