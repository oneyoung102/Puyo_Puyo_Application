#include <SFML/Graphics.hpp>
#include "puyoPrintNextPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"

#include <tuple>

using namespace puyoImageConstant;
using namespace puyoGameConstant;
using namespace std;
using namespace sf;

puyoPrintNextPuyo::puyoPrintNextPuyo(int player_num, const int& new_puyo_count, const vector<pair<puyoType,puyoType>>& new_colors, Sprite puyo, POSf pos, int life)
    : puyoPrintObject(puyo,pos,life),
    new_colors(new_colors),
    new_puyo_count(new_puyo_count)
{
    this->player_num = player_num;
}

void puyoPrintNextPuyo::print(RenderWindow& w)
{
    const auto[color1,color2] = new_colors[new_puyo_count];
    const auto[color3,color4] = new_colors[new_puyo_count+1];
    const auto pos1 = pos+POSf(((player_num == 0) ? NEXT_PUYO_VIEWER_BREADTH : -NEXT_PUYO_VIEWER_BREADTH),PUYO_SIZE);
    const vector<tuple<puyoType,POSf>> next_puyos = {{color2,pos},{color1,pos+POSf(0,PUYO_SIZE)},{color4,pos1},{color3,pos1+POSf(0,PUYO_SIZE)}};
    for(const auto [type, screen_pos] : next_puyos)
        print_puyo(w,type,screen_pos);
}