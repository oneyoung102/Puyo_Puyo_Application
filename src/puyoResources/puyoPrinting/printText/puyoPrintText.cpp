#include "puyoPrintText.hpp"
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

puyoPrintText::puyoPrintText(POSf pos, const string& content, const Font& font, int size, sf::Color color, sf::Text::Style style, int life)
    : text(Text(font))
{
    this->life = life; // life == -1 일 때는 영생
    text.setString(content);
    text.setFillColor(color);
    text.setStyle(style);
    text.setCharacterSize(size);

    // 중심 정렬을 위해 origin을 텍스트 중앙으로 설정
    auto bounds = text.getLocalBounds();
    text.setOrigin({
        bounds.position.x + bounds.size.x / 2.f,
        bounds.position.y + bounds.size.y / 2.f
    });
    text.setPosition(Vector2f(pos.x,pos.y));
}

bool puyoPrintText::alive(){return life != 0;}

void puyoPrintText::print(RenderWindow& window)
{
    window.draw(text);
    if(alive())
        --life;
}
