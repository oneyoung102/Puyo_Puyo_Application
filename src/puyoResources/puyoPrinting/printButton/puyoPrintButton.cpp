#include "puyoPrintButton.hpp"
#include <SFML/Graphics.hpp>
#include <string>

#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

using namespace std;
using namespace sf;
using namespace puyoImageConstant;

puyoPrintButton::puyoPrintButton(sf::Sprite s, const bool& selected, double x, double y, string content, Font& font, double scaling, sf::Color color, sf::Text::Style style, int life)
    : text(Text(font))
    , selected(selected)
    , sprite(s)
{
    this->life = life; // life == -1 일 때는 영생
    text.setString(content);
    text.setFillColor(color);
    text.setStyle(style);

    text.setCharacterSize(TEXT_SIZE_IN_BUTTON*scaling);
    sprite.setScale({(float)scaling,(float)scaling});

    // 중심 정렬을 위해 origin을 텍스트 중앙으로 설정
    auto bounds0 = text.getLocalBounds();
    text.setOrigin({
        bounds0.position.x + bounds0.size.x / 2.f,
        bounds0.position.y + bounds0.size.y / 2.f
    });
    text.setPosition({(float)x, (float)y});

    const auto [X,Y] = sprite.getTexture().getSize();
    button_x = X;
    button_y = ceil(Y/2.0);
    sprite.setTextureRect(IntRect({0,0}, {button_x,button_y}));
    auto bounds1 = sprite.getLocalBounds();
    sprite.setOrigin({
        bounds1.position.x + bounds1.size.x / 2.f,
        bounds1.position.y + bounds1.size.y / 2.f
    });
    sprite.setPosition({(float)x, (float)y});
}

bool puyoPrintButton::alive(){return life != 0;}

void puyoPrintButton::print(RenderWindow& window)
{
    if(selected)
        sprite.setTextureRect(IntRect({0,button_y}, {button_x, button_y}));
    else
        sprite.setTextureRect(IntRect({0, 0}, {button_x, button_y}));
    window.draw(sprite);
    window.draw(text);
    if(alive())
        --life;
}
