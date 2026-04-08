#include "puyoPrintDialButton.hpp"
#include <SFML/Graphics.hpp>
#include <string>

#include "puyoResources/puyoPrinting/printButton/puyoPrintButton.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

using namespace std;
using namespace sf;
using namespace puyoImageConstant;

puyoPrintDialButton::puyoPrintDialButton(sf::Sprite s, const bool& selected, const bool& dial_selected, float x, float y, string content, Font& font, float scaling, sf::Color color, sf::Text::Style style, int life)
    : puyoPrintButton(s,selected,x,y,content,font,scaling,color,style,life)
    , dial_selected(dial_selected)
{

}
void puyoPrintDialButton::print(RenderWindow& window)
{
    if(selected)
    {
        if(dial_selected)
            sprite.setTextureRect(IntRect({0,button_y}, {button_x, button_y}));
        else
            sprite.setTextureRect(IntRect({0,0}, {button_x, button_y}));
        window.draw(sprite);
        window.draw(text);
    }  
    if(alive())
        --life;
}
