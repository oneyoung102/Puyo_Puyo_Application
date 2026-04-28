#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include "puyoPuyoVanish.hpp"

using namespace std;

puyoPuyoVanish::puyoPuyoVanish(int amount) : puyoPuyoAct(amount){};

void puyoPuyoVanish::act(puyoPuyo& puyo)
{
    ++act_count;
};

