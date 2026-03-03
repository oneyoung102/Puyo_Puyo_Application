#include "puyoPageManager.hpp"
#include "puyoPage.hpp"
#include "puyoPageSignal.hpp"

#include "openingPage/puyoOpeningPage.hpp"
#include "menuPage/puyoMenuPage.hpp"
#include "readyPage/puyoReadyPage.hpp"
#include "gamePage/puyoGamePage.hpp"
#include "endingPage/puyoEndingPage.hpp"

#include <SFML/Graphics.hpp>


using namespace std;
using namespace sf;

void puyoPageManager::convert_page(Page p)
{
    switch(p)
    {
        case Page::opening :
            curr_page = make_unique<puyoOpeningPage>(pfs);
            break;
        case Page::menu :
            curr_page = make_unique<puyoMenuPage>(pfs);
            break;
        case Page::ready :
            curr_page = make_unique<puyoReadyPage>(pfs);
            break;        
        case Page::game :
            curr_page = make_unique<puyoGamePage>(pfs,*signal.play_mode,*signal.condition,*signal.gravity,*signal.stay,*signal.colors);
            break;
        case Page::ending :
            curr_page = make_unique<puyoEndingPage>(pfs,*signal.win_player_num,capture_sprite,*signal.play_mode);
            break;
    };
}
puyoPageManager::puyoPageManager()
    : capture_sprite(Sprite(capture_texture))
{
    signal = puyoPageSignal{Page::opening,Play_mode::solo,4,1800,2000,4,-1,false};
    convert_page(*signal.next_page);
}

void puyoPageManager::show_page(RenderWindow& window)
{
    while (auto event = window.pollEvent())
    {
        if (event->is<Event::Closed>())
            window.close();
        curr_page->get_let().detect_keyboard(event);
    }
    window.clear();

    signal = curr_page->proceed_page(pfs, window);
    if(signal.next_page)
        convert_page(*signal.next_page);
    
    window.display();
    if (signal.request_capture && *signal.request_capture)
    {
        capture_texture = sf::Texture(window.getSize()); 
        capture_texture.update(window);
        capture_sprite.setTexture(capture_texture, true);
    }
}
