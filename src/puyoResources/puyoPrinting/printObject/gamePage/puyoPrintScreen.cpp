#include <SFML/Graphics.hpp>
#include "puyoPrintScreen.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

using namespace puyoImageConstant;
using namespace sf;

puyoPrintScreen::puyoPrintScreen(int player_count, Sprite screen, int life) : puyoPrintObject(screen,POSf(),life)
{
    sprite.setTextureRect(IntRect({(int)SCREEN_X*(2-player_count), 0}, {(int)SCREEN_X,(int)SCREEN_Y})); 
}