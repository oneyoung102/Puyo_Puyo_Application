#include <SFML/Graphics.hpp>

#include "puyoPage/puyoLet.hpp"

#include <optional>
#include <functional>
#include <vector>

using namespace std;
using namespace sf;

puyoLet::puyoLet()
{
    key_allot = vector<function<void()>>(101);  //sf::Keyboard::Key에서 key는 0 ~ 100번 까지
}

void puyoLet::act_keyboard_let(const optional<Event>& event)
{
    if(!event)
        return;
    if(auto* key = event->getIf<Event::KeyPressed>())
    {
        auto& func = key_allot[(int)key->code];
        if(func)
            func();
    }
}
void puyoLet::allot_key(int key, function<void()> func){key_allot[key] = func;}
void puyoLet::clear_allot()
{
    key_allot = vector<function<void()>>(101);
}