#include <SFML/Graphics.hpp>
#include "puyoPrintScreenhead.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

using namespace puyoImageConstant;
using namespace sf;

puyoPrintScreenhead::puyoPrintScreenhead(Sprite screen, int life) : puyoPrintObject(screen,life)
{
    const auto [ignore,player_board_y] = PLAYER_BOARD_POS[0];
    sprite.setTextureRect(IntRect({0,0}, {(int)(SCREEN_X),(int)player_board_y+1})); 
}