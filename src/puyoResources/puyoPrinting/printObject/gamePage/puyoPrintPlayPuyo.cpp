#include <SFML/Graphics.hpp>
#include "puyoPrintPlayPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoPlayer/puyoPlayer.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

using namespace puyoImageConstant;
using namespace std;
using namespace sf;

puyoPrintPlayPuyo::puyoPrintPlayPuyo(const puyoPlayer& player, Sprite puyo, POSf pos, int life)
    : puyoPrintObject(puyo,pos,life)
    , player(player)
{}

void puyoPrintPlayPuyo::print(RenderWindow& w)
{
    const auto& play_puyo = player.refer_puyo();
    const auto& [pos1,pos2] = play_puyo.get_pos();
    const auto& [puyo1,puyo2] = play_puyo.view();
    print_puyo(w,puyo1,pos+pos1*PUYO_SIZE);
    print_puyo(w,puyo2,pos+pos2*PUYO_SIZE);
}