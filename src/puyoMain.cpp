#include "puyoPage/puyoPageManager.hpp"
#include <SFML/Graphics.hpp>
#include "puyoResources/puyoImageConstant.hpp"

using namespace sf;
using namespace puyoImageConstant;

int main()
{   
    puyoPageManager page;
    RenderWindow window(VideoMode({SCREEN_X, SCREEN_Y}),"Puyo Puyo"); //창 설정
    window.setView(window.getDefaultView());
    while(window.isOpen())
    {
        window.clear();
        page.show_page(window);
        window.display();
    }
    return 0;
}