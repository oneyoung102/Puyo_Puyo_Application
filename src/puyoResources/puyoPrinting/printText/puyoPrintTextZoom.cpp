#include "puyoPrintText.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"
#include "puyoPrintTextZoom.hpp"
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

puyoPrintTextZoom::puyoPrintTextZoom(POSf pos, string content, int cycle, Font& font, int size, sf::Color color, sf::Text::Style style, int life)
    : puyoPrintText(pos,content,font,size,color,style,life)
    , cycle(cycle)
    , dsize(max(1,size/puyoImageConstant::TEXT_ZOOM_SIZE_PROP))
    , dcycle(max(1,cycle/puyoImageConstant::TEXT_ZOOM_CYCLE_PROP))
{
    cycle_count = 0;
    cycle_back = true;
    this->size = size;
}
void puyoPrintTextZoom::print(RenderWindow& window)
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
    if(alive())
        --life;
}
