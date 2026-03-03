#include "puyoPrintText.hpp"
#include "puyoPrintTextZoom.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <cmath>

using namespace std;
using namespace sf;

puyoPrintTextZoom::puyoPrintTextZoom(float x, float y, string content, Font& font, int size_temp, sf::Color color, sf::Text::Style style, int l, int c)
    : puyoPrintText(x,y,content,font,size_temp,color,style,l)
{
    cycle = c;
    cycle_count = 0;
    cycle_back = true;
    size = size_temp;
    dsize = max(1,size/30);
    dcycle = max(1,cycle/15);
}
void puyoPrintTextZoom::print_text(RenderWindow& window)
{
    if(++cycle_count >= cycle)
    {
        cycle_back ^= 1;
        cycle_count = 0;
    }
    if(cycle_count%dcycle == 0)
    {
        auto bounds = text.getLocalBounds();
        text.setOrigin({bounds.position.x + bounds.size.x / 2.f,bounds.position.y + bounds.size.y / 2.f});
        if(cycle_back)
            text.setCharacterSize(size+=dsize);
        else
            text.setCharacterSize(size-=dsize);
    }
    window.draw(text);
    if(is_alive())
        --life;
}
