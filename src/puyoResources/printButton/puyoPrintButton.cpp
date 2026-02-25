#include "puyoPrintButton.hpp"
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

puyoPrintButton::puyoPrintButton(sf::Sprite uss, sf::Sprite ss, bool& selected_temp, float x, float y, string content, Font& font, int size, sf::Color color, sf::Text::Style style, int l)
    : text(Text(font))
    , selected(selected_temp)
    , unselected_sprite(uss)
    , selected_sprite(ss)
{
    life = l; // life == -1 일 때는 영생
    text.setString(content);
    text.setFillColor(color);
    text.setStyle(style);
    text.setCharacterSize(size);

    // 중심 정렬을 위해 origin을 텍스트 중앙으로 설정
    auto bounds0 = text.getLocalBounds();
    text.setOrigin({
        bounds0.position.x + bounds0.size.x / 2.f,
        bounds0.position.y + bounds0.size.y / 2.f
    });
    text.setPosition({x, y});

    auto bounds1 = unselected_sprite.getLocalBounds();
    unselected_sprite.setOrigin({
        bounds1.position.x + bounds1.size.x / 2.f,
        bounds1.position.y + bounds1.size.y / 2.f
    });
    unselected_sprite.setPosition({x, y});

    auto bounds2 = selected_sprite.getLocalBounds();
    selected_sprite.setOrigin({
        bounds2.position.x + bounds2.size.x / 2.f,
        bounds2.position.y + bounds2.size.y / 2.f
    });
    selected_sprite.setPosition({x, y});
}

bool puyoPrintButton::is_alive(){return life != 0;}

void puyoPrintButton::print_button(RenderWindow& window)
{
    if(selected)
        window.draw(selected_sprite);
    else
        window.draw(unselected_sprite);
    window.draw(text);
    if(is_alive())
        --life;
}
