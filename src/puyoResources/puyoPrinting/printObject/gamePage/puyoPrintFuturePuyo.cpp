#include <SFML/Graphics.hpp>
#include "puyoPrintFuturePuyo.hpp"
#include "puyoPage/pages/gamePage/puyoTempPuyo/puyoFuturePuyo.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

#include <vector>

using namespace puyoImageConstant;
using namespace std;
using namespace sf;

puyoPrintFuturePuyo::puyoPrintFuturePuyo(vector<puyoFuturePuyo>& fp, Sprite puyo, int x, int y, int life) : puyoPrintObject(puyo,x,y,life), future_puyos(fp)
{
    sprite.setColor(Color(255, 255, 255, 128*FUTURE_PUYO_ALPHA_VALUE));//투명도 조절
}

void puyoPrintFuturePuyo::print_object(RenderWindow& w)
{
    for(auto&& future_puyo : future_puyos)
    {
        const auto puyo = future_puyo.get_puyo_color();
        const auto [px,py] = future_puyo.get_puyo_pos();
        print_puyo(w,puyo,x+PUYO_SIZE*px,y +PUYO_SIZE*py);
    }
}