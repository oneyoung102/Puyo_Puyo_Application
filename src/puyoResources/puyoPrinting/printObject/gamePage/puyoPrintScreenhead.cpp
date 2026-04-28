#include <SFML/Graphics.hpp>
#include "puyoPrintScreenhead.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include "puyoTool/puyoCast.hpp"

using namespace puyoImageConstant;
using namespace puyoGameConstant;
using namespace sf;

puyoPrintScreenhead::puyoPrintScreenhead(Sprite screen, int life) : puyoPrintObject(screen,life)
{
    const auto [_,player_board_y] = PLAYER_BOARD_POS[0];
    sprite.setTextureRect(IntRect({0,0}, {CASTi(SCREEN_X),CASTi(player_board_y)+1})); 
}