#include <SFML/Graphics.hpp>
#include "puyoPrintScreen.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

using namespace puyoImageConstant;
using namespace sf;

puyoPrintScreen::puyoPrintScreen(int pc, Sprite screen, int x, int y, int life) : puyoPrintObject(screen,x,y,life)
{
    player_count = pc;
    sprite.setTextureRect(IntRect({static_cast<int>(SCREEN_X)*(2-player_count), 0}, {static_cast<int>(SCREEN_X),static_cast<int>(SCREEN_Y)})); 
}

void puyoPrintScreen::print_object(RenderWindow& w)
{
    print_sprite(w,x,y);
}