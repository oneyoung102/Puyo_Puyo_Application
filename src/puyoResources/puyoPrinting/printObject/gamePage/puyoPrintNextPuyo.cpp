#include <SFML/Graphics.hpp>
#include "puyoPrintNextPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/puyoType.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"

#include <tuple>

using namespace puyoImageConstant;
using namespace puyoGameConstant;
using namespace std;
using namespace sf;

puyoPrintNextPuyo::puyoPrintNextPuyo(int player_num, const int& new_puyo_count, const vector<pair<puyoPuyo,puyoPuyo>>& new_types, Sprite puyo, POSf pos, int life)
    : puyoPrintObject(puyo,pos,life)
    , new_types(new_types)
    , new_puyo_count(new_puyo_count)
    , player_num(player_num)
{}

void puyoPrintNextPuyo::print(RenderWindow& w)
{
    const auto& [puyo1,puyo2] = new_types[new_puyo_count];
    const auto& [puyo3,puyo4] = new_types[new_puyo_count+1];
    const auto pos1 = pos+POSf(((player_num == 0) ? NEXT_PUYO_VIEWER_BREADTH : -NEXT_PUYO_VIEWER_BREADTH),PUYO_SIZE);
    const vector<pair<puyoPuyo,POSf>>& next_puyos = {{puyo2,pos},{puyo1,pos+POSf(0,PUYO_SIZE)},{puyo4,pos1},{puyo3,pos1+POSf(0,PUYO_SIZE)}};
    for(const auto& [puyo, screen_pos] : next_puyos)
        print_puyo(w,puyo,screen_pos);
}