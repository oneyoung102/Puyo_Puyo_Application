#include "puyoPrintDialButton.hpp"
#include <SFML/Graphics.hpp>
#include <string>

#include "puyoResources/puyoPrinting/printButton/puyoPrintButton.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

using namespace std;
using namespace sf;
using namespace puyoImageConstant;

puyoPrintDialButton::puyoPrintDialButton(sf::Sprite s, const bool& selected_temp, const bool& dial_selected_temp, float x, float y, string content, Font& font, float scaling, sf::Color color, sf::Text::Style style, int l)
    : puyoPrintButton(s,selected_temp,x,y,content,font,scaling,color,style,l)
    , dial_selected(dial_selected_temp)
{

}
void puyoPrintDialButton::print_button(RenderWindow& window)
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
    if(is_alive())
        --life;
}
