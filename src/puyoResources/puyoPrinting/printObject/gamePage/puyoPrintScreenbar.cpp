#include <SFML/Graphics.hpp>
#include "puyoPrintScreenbar.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

using namespace puyoImageConstant;
using namespace sf;

puyoPrintScreenbar::puyoPrintScreenbar(int player_count, Sprite screen, int x, int y, int life) : puyoPrintObject(screen,x,y,life)
{
    sprite.setTextureRect(IntRect({static_cast<int>(SCREEN_X)*(2-player_count)+SCREEN_BAR_FROM_X,SCREEN_BAR_FROM_Y}, {SCREEN_BAR_TO_X,SCREEN_BAR_TO_Y})); 
}

void puyoPrintScreenbar::print_object(RenderWindow& w)
{
    print_sprite(w,x,y);
}