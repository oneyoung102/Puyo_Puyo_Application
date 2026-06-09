#include "puyoPrintButton.hpp"
#include <SFML/Graphics.hpp>
#include <string>

#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

using namespace std;
using namespace sf;
using namespace puyoImageConstant;

puyoPrintButton::puyoPrintButton(sf::Sprite s, const bool& selected, POSf pos, const string& content, const Font& font, float scaling, sf::Color color, sf::Text::Style style, int life)
    : text(Text(font))
    , selected(selected)
    , sprite(s)
    , life(life)
{
    text.setString(content);
    text.setFillColor(color);
    text.setStyle(style);

    text.setCharacterSize(TEXT_SIZE_IN_BUTTON*scaling);
    sprite.setScale({scaling,scaling});

    // 중심 정렬을 위해 origin을 텍스트 중앙으로 설정
    auto bounds0 = text.getLocalBounds();
    text.setOrigin({
        bounds0.position.x + bounds0.size.x / 2.f,
        bounds0.position.y + bounds0.size.y / 2.f
    });
    text.setPosition(Vector2f(pos.x,pos.y));
    
    auto bounds1 = sprite.getLocalBounds();
    sprite.setOrigin({
        bounds1.position.x + bounds1.size.x / 2.f,
        bounds1.position.y + bounds1.size.y / 2.f
    });
    sprite.setPosition(Vector2f(pos.x,pos.y));
}

bool puyoPrintButton::alive(){return life != 0;}
bool puyoPrintButton::is_immortal(){return life == puyoImageConstant::PRINT_IMMORTAL;}

void puyoPrintButton::print(RenderWindow& window, const Shader& shader)
{
    if(selected) 
        window.draw(sprite,&shader);
    else 
        window.draw(sprite);
    window.draw(text);
    if(alive())
        --life;
}
