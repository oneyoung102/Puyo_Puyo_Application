#include "puyoPrintTextFlash.hpp"
#include "puyoPrintText.hpp"
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

puyoPrintTextFlash::puyoPrintTextFlash(POSf pos, const string& content, const Font& font, int size, int cycle, sf::Color color, sf::Text::Style style, int life)
    : puyoPrintText(pos,content,font,size,color,style,life)
    , cycle(cycle)
    , cycle_count(0)
    , show(true)
{}

void puyoPrintTextFlash::print(RenderWindow& window)
{
    if(++cycle_count >= cycle)
    {
        show = !show;
        cycle_count = 0;
    }
    if(show)
        window.draw(text);
    if(alive())
        --life;
}
