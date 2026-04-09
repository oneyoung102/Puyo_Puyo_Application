#include "puyoPrintTextFlash.hpp"
#include "puyoPrintText.hpp"
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

puyoPrintTextFlash::puyoPrintTextFlash(double x, double y, string content, Font& font, int size, sf::Color color, sf::Text::Style style, int life, int cycle)
    : puyoPrintText(x,y,content,font,size,color,style,life)
    , cycle(cycle)
{
    cycle_count = 0;
    cycle_back = true;
}
void puyoPrintTextFlash::print(RenderWindow& window)
{
    if(++cycle_count >= cycle)
    {
        cycle_back ^= 1;
        cycle_count = 0;
    }
    if(cycle_back)
        window.draw(text);
    if(alive())
        --life;
}
