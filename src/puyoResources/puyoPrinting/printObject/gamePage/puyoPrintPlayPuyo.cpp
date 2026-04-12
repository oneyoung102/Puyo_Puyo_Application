#include <SFML/Graphics.hpp>
#include "puyoPrintPlayPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoPlayer/puyoPlayer.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

using namespace puyoImageConstant;
using namespace std;
using namespace sf;

puyoPrintPlayPuyo::puyoPrintPlayPuyo(puyoPlayer& player, Sprite puyo, std::pair<int,int> pos, int life) : puyoPrintObject(puyo,pos,life), player(player){}

void puyoPrintPlayPuyo::print(RenderWindow& w)
{
    const auto& play_puyo = player.get_puyo();
    const auto[px1,py1,px2,py2] = play_puyo.get_pos();
    const auto[type1,type2] = play_puyo.get_type();
    print_puyo(w,type1,{x+PUYO_SIZE*px1,y+PUYO_SIZE*py1});
    print_puyo(w,type2,{x+PUYO_SIZE*px2,y+PUYO_SIZE*py2});
}