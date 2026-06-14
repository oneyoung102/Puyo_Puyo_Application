#include <SFML/Graphics.hpp>

#include "puyoPage/puyoKeyBoard/puyoLet.hpp"

using namespace std;
using namespace sf;

puyoLet::puyoLet()
{
    clear();
}  

void puyoLet::act_keyboard_let(const optional<Event>& event)
{
    if(!event)
        return;
    if(auto* key = event->getIf<Event::KeyPressed>())
    {
        if(key->code == sf::Keyboard::Key::Unknown)
            return;
        auto& func = key_allot[static_cast<size_t>(key->code)];
        if(func)
            func();
    }
}
void puyoLet::allot_key(Keyboard::Key key, function<void()> func){key_allot[static_cast<size_t>(key)] = func;}
void puyoLet::clear()
{
    key_allot.fill(nullptr);
}
void puyoLet::clear(Keyboard::Key key)
{
    key_allot[static_cast<size_t>(key)] = nullptr;
}