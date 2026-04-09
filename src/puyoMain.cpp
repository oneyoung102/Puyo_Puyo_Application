#include "puyoPage/puyoPageManager/puyoPageManager.hpp"
#include <SFML/Graphics.hpp>
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

using namespace sf;
using namespace puyoImageConstant;

int main()
{   
    sf::Clock clock;
    const int frame_value = 60;
    puyoPageManager page;
    RenderWindow window(VideoMode({SCREEN_X, SCREEN_Y}),"Puyo Puyo"); //창 설정
    window.setView(window.getDefaultView());
    while(window.isOpen())
    {
        const double dt = clock.restart().asSeconds();
        page.show_page(window);
        sf::sleep(sf::microseconds(fmax(0,frame_value-dt*1000)));
    }
    return 0;
}