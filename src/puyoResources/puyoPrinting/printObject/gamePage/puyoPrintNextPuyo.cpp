#include <SFML/Graphics.hpp>
#include "puyoPrintNextPuyo.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"

using namespace puyoImageConstant;
using namespace puyoGameConstant;
using namespace std;
using namespace sf;

puyoPrintNextPuyo::puyoPrintNextPuyo(int player_num, const int& new_puyo_count, decltype(new_puyos)& new_puyos, Sprite puyo, POSf pos, int life)
    : puyoPrintObject(puyo,pos,life)
    , new_puyos(new_puyos)
    , new_puyo_count(new_puyo_count)
    , player_num(player_num)
{}

void puyoPrintNextPuyo::print(RenderWindow& w)
{
    const auto& [puyo1,puyo2] = new_puyos.view(new_puyo_count);
    const auto& [puyo3,puyo4] = new_puyos.view(new_puyo_count+1);
    const auto pos1 = pos+POSf(((player_num == 0) ? NEXT_PUYO_VIEWER_BREADTH : -NEXT_PUYO_VIEWER_BREADTH),PUYO_SIZE);
    const vector<pair<puyoPuyo,POSf>>& next_puyos = {{puyo2,pos},{puyo1,pos+POSf(0,PUYO_SIZE)},{puyo4,pos1},{puyo3,pos1+POSf(0,PUYO_SIZE)}};
    for(const auto& [puyo, screen_pos] : next_puyos)
        print_puyo(w,puyo,screen_pos);
}