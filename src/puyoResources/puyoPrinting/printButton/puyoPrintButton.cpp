#include "puyoPrintButton.hpp"
#include <SFML/Graphics.hpp>
#include <string>

#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

using namespace std;
using namespace sf;
using namespace puyoImageConstant;

puyoPrintButton::puyoPrintButton(sf::Sprite s, const bool& selected_temp, float x, float y, string content, Font& font, float scaling, sf::Color color, sf::Text::Style style, int l)
    : text(Text(font))
    , selected(selected_temp)
    , sprite(s)
{
    life = l; // life == -1 일 때는 영생
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
    text.setPosition({x, y});

    const auto [X,Y] = sprite.getTexture().getSize();
    button_x = X;
    button_y = Y/2;
    sprite.setTextureRect(IntRect({0,0}, {button_x,button_y}));
    auto bounds1 = sprite.getLocalBounds();
    sprite.setOrigin({
        bounds1.position.x + bounds1.size.x / 2.f,
        bounds1.position.y + bounds1.size.y / 2.f
    });
    sprite.setPosition({x, y});
}

bool puyoPrintButton::is_alive(){return life != 0;}

void puyoPrintButton::print_button(RenderWindow& window)
{
    if(selected)
        sprite.setTextureRect(IntRect({0,button_y}, {button_x, button_y}));
    else
        sprite.setTextureRect(IntRect({0, 0}, {button_x, button_y}));
    window.draw(sprite);
    window.draw(text);
    if(is_alive())
        --life;
}
