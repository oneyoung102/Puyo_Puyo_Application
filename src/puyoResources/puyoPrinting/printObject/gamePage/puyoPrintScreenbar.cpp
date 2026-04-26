#include <SFML/Graphics.hpp>
#include "puyoPrintScreenbar.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

using namespace puyoImageConstant;
using namespace sf;

puyoPrintScreenbar::puyoPrintScreenbar(int player_count, Sprite screen, int life)
    : puyoPrintObject(screen,SCREEN_BAR_FROM_POS,life)
{
    sprite.setTextureRect(IntRect({static_cast<int>(SCREEN_X)*(2-player_count)+SCREEN_BAR_FROM_X,SCREEN_BAR_FROM_Y}, {SCREEN_BAR_TO_X,SCREEN_BAR_TO_Y})); 
}