#include <SFML/Graphics.hpp>
#include "puyoPrintFuturePuyo.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

#include <vector>

using namespace puyoImageConstant;
using namespace std;
using namespace sf;

puyoPrintFuturePuyo::puyoPrintFuturePuyo(const vector<puyoPuyo>& future_puyos, Sprite puyo, POSf pos, int life)
    : puyoPrintObject(puyo,pos,life)
    , future_puyos(future_puyos)
{
    sprite.setColor(Color(255, 255, 255, 128*FUTURE_PUYO_ALPHA_VALUE));//투명도 조절
}

void puyoPrintFuturePuyo::print(RenderWindow& w)
{
    for(const auto& future_puyo : future_puyos)
        print_puyo(w,future_puyo,pos+future_puyo.get_pos()*PUYO_SIZE);
}