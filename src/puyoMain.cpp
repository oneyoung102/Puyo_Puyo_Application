#include "puyoPage/puyoPageManager/puyoPageManager.hpp"
#include <SFML/Graphics.hpp>
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

using namespace sf;
using namespace puyoImageConstant;

int main()
{   
    puyoPageManager page;
    RenderWindow window(VideoMode(SCREEN_SIZE), "Puyo Puyo"); // 창 설정
    window.setView(window.getDefaultView());

    window.setFramerateLimit(600); 
    while(window.isOpen())
    {
        page.show_page(window);
    }
    return 0;
}
