#include "puyoPageManager.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include "puyoPage/pages/puyoPage.hpp"
#include "puyoPage/puyoPageManager/puyoPageSignal.hpp"

#include "puyoPage/pages/openingPage/puyoOpeningPage.hpp"
#include "puyoPage/pages/menuPage/puyoMenuPage.hpp"
#include "puyoPage/pages/readyPage/puyoReadyPage.hpp"
#include "puyoPage/pages/gamePage/puyoGamePage.hpp"
#include "puyoPage/pages/endingPage/puyoEndingPage.hpp"

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

void puyoPageManager::capture_window(sf::RenderWindow& window)
{
    capture_texture = sf::Texture(window.getSize()); 
    capture_texture.update(window);
    capture_sprite.setTexture(capture_texture, true);
}

puyoPageManager::puyoPageManager()
    : capture_sprite(Sprite(capture_texture))
{
    signal = puyoPageSignal{Page::opening,Play_mode::solo,4,-1,-1,-1,puyoGameConstant::NO_WINNER,false};
    convert_page(*signal.next_page);
}

void puyoPageManager::show_page(RenderWindow& window)
{
    while (auto event = window.pollEvent())
    {
        if (event->is<Event::Closed>())
            window.close();
        curr_page->get_let().act_keyboard_let(event);
    }
    window.clear();
    signal = curr_page->proceed_page(pfs, window);
    window.display();
    
    if (signal.request_capture && *signal.request_capture)
    {
        capture_window(window);
        signal.request_capture = false;

    }
    if(signal.next_page)
        convert_page(*signal.next_page);
}
