#include <SFML/Graphics.hpp>

#include "puyoPage/puyoLet.hpp"
#include "puyoTool/puyoCast.hpp"

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
        auto& func = key_allot[CASTs(key->code)];
        if(func)
            func();
    }
}
void puyoLet::allot_key(Keyboard::Key key, function<void()> func){key_allot[CASTs(key)] = func;}
void puyoLet::clear()
{
    key_allot = vector<function<void()>>(101);
}

#define FUNCFY(x) [this](){return x();}