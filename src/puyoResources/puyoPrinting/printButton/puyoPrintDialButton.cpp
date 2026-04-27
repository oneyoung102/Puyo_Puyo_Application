#include "puyoPrintDialButton.hpp"
#include <SFML/Graphics.hpp>
#include <string>

#include "puyoResources/puyoPrinting/printButton/puyoPrintButton.hpp"

using namespace std;
using namespace sf;

puyoPrintDialButton::puyoPrintDialButton(sf::Sprite s, const bool& selected, const bool& dial_selected, POSf pos, string content, Font& font, float scaling, sf::Color color, sf::Text::Style style, int life)
    : puyoPrintButton(s,selected,pos,content,font,scaling,color,style,life)
    , dial_selected(dial_selected)
{

}
void puyoPrintDialButton::print(RenderWindow& window)
{
    if(selected)
    {
        if(dial_selected)
            sprite.setTextureRect(IntRect({0,img_pos.y}, {img_pos.x, img_pos.y}));
        else
            sprite.setTextureRect(IntRect({0, 0}, {img_pos.x, img_pos.y}));
        window.draw(sprite);
        window.draw(text);
    }  
    if(alive())
        --life;
}
