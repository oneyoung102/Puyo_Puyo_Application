#pragma once

#include <SFML/Graphics.hpp>

#include <optional>
#include <functional>
#include <vector>

using namespace std;
using namespace sf;

class puyoLet
{
    private :
        vector<function<void()>> key_allot;
    public :
        puyoLet();
        bool detect_keyboard(const optional<Event>& event);
        void allot_key(int key, function<void()> func);
};