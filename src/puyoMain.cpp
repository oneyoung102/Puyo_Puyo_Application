#include "puyoPage/puyoPageManager/puyoPageManager.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdexcept>
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

using namespace sf;
using namespace puyoImageConstant;

int main()
{   
    puyoPageManager page;
    RenderWindow window(VideoMode(SCREEN_SIZE), "Puyo Puyo"); // 창 설정
    window.setView(window.getDefaultView());

    window.setFramerateLimit(120); 
    while(window.isOpen())
    {
        try
        {
            page.show_page(window);
        }
        catch(const std::runtime_error& e)
        {
            std::cerr << e.what() << std::endl;
            window.close();
            break;
        }
    }
    return 0;
}
