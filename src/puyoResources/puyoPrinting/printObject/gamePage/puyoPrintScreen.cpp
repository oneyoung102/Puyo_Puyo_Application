#include <SFML/Graphics.hpp>
#include "puyoPrintScreen.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"
#include "puyoTool/puyoCast.hpp"

using namespace puyoImageConstant;
using namespace sf;

puyoPrintScreen::puyoPrintScreen(int player_count, Sprite screen, int life)
    : puyoPrintObject(screen,POSf(),life)
{
    sprite.setTextureRect(IntRect({CASTi(SCREEN_X)*(2-player_count), 0}, {CASTi(SCREEN_X),CASTi(SCREEN_Y)})); 
}