#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include <memory>
#include "puyoPuyoVanish.hpp"

using namespace std;

puyoPuyoVanish::puyoPuyoVanish(int amount) : puyoPuyoAct(amount){};
std::unique_ptr<puyoPuyoAct> puyoPuyoVanish::clone() const
{
    auto temp = make_unique<puyoPuyoVanish>(act_count_init);
    temp->let(act_count);
    return temp;
}

void puyoPuyoVanish::act(puyoPuyo& puyo)
{
    ++act_count;
};

