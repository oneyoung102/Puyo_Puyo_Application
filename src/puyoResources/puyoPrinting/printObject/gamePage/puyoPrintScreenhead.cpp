#include <SFML/Graphics.hpp>
#include "puyoPrintScreenhead.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

using namespace puyoImageConstant;
using namespace sf;

puyoPrintScreenhead::puyoPrintScreenhead(Sprite screen, int x, int y, int life) : puyoPrintObject(screen,x,y,life)
{
    const auto [ignore,player_board_y] = PLAYER_BOARD_POS[0];
    sprite.setTextureRect(IntRect({0,0}, {static_cast<int>(SCREEN_X),player_board_y+1})); 
}

void puyoPrintScreenhead::print_object(RenderWindow& w)
{
    print_sprite(w,x,y);
}