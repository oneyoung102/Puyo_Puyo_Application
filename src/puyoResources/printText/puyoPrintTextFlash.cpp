#include "puyoPrintTextFlash.hpp"
#include "puyoPrintText.hpp"
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

puyoPrintTextFlash::puyoPrintTextFlash(float x, float y, string content, Font& font, int size, sf::Color color, sf::Text::Style style, int l, int c)
    : puyoPrintText(x,y,content,font,size,color,style,l)
{
    cycle = c;
    cycle_count = 0;
    cycle_back = true;
}
void puyoPrintTextFlash::print_text(RenderWindow& window)
{
    if(++cycle_count >= cycle)
    {
        cycle_back ^= 1;
        cycle_count = 0;
    }
    if(cycle_back)
        window.draw(text);
    if(is_alive())
        --life;
}
