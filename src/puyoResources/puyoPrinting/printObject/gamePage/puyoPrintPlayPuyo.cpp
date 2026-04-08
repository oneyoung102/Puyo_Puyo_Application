#include <SFML/Graphics.hpp>
#include "puyoPrintPlayPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoType.hpp"
#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

#include <tuple>
#include <vector>

using namespace puyoImageConstant;
using namespace std;
using namespace sf;

puyoPrintPlayPuyo::puyoPrintPlayPuyo(puyoPlayPuyo& play_puyo, Sprite puyo, int x, int y, int life) : puyoPrintObject(puyo,x,y,life), play_puyo(play_puyo){}

void puyoPrintPlayPuyo::print(RenderWindow& w)
{
    const auto [x1,y1,x2,y2] = play_puyo.get_pos();
    const auto [color1,color2] = play_puyo.get_types();
    const vector<tuple<puyoType,int,int>> play_puyos = {{color1,x + PUYO_SIZE*x1,y + PUYO_SIZE*y1},{color2,x + PUYO_SIZE*x2,y + PUYO_SIZE*y2}};
    for(const auto [type, px, py] : play_puyos)
        print_puyo(w,type,px,py);
}