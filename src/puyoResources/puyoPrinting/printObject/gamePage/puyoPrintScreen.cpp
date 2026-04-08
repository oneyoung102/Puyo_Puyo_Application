#include <SFML/Graphics.hpp>
#include "puyoPrintScreen.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

using namespace puyoImageConstant;
using namespace sf;

puyoPrintScreen::puyoPrintScreen(int player_count, Sprite screen, int x, int y, int life) : puyoPrintObject(screen,x,y,life)
{
    this->player_count = player_count;
    sprite.setTextureRect(IntRect({static_cast<int>(SCREEN_X)*(2-player_count), 0}, {static_cast<int>(SCREEN_X),static_cast<int>(SCREEN_Y)})); 
}

void puyoPrintScreen::print(RenderWindow& w)
{
    print_sprite(w,x,y);
}