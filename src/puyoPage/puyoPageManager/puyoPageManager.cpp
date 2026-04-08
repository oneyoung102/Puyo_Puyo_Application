#include "puyoPageManager.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include "puyoPage/pages/puyoPage.hpp"
#include "puyoPage/puyoPageManager/puyoPageSignal.hpp"

#include "puyoPage/pages/openingPage/puyoOpeningPage.hpp"
#include "puyoPage/pages/menuPage/puyoMenuPage.hpp"
#include "puyoPage/pages/optionPage/puyoOptionPage.hpp"
#include "puyoPage/pages/gamePage/puyoGamePage.hpp"
#include "puyoPage/pages/endingPage/puyoEndingPage.hpp"

#include <SFML/Graphics.hpp>


using namespace std;
using namespace sf;

void puyoPageManager::change_page(Page p)
{
    switch(p)
    {
        case Page::opening :
            curr_page = make_unique<puyoOpeningPage>(pfs);
            break;
        case Page::menu :
            curr_page = make_unique<puyoMenuPage>(pfs);
            break;
        case Page::option :
            curr_page = make_unique<puyoOptionPage>(pfs);
            break;        
        case Page::game :
            curr_page = make_unique<puyoGamePage>(pfs,*signal.arcade,*signal.diff,*signal.mode);
            break;
        case Page::ending :
            curr_page = make_unique<puyoEndingPage>(pfs,*signal.win_player_num,capture_sprite,*signal.arcade);
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
    signal = puyoPageSignal{Page::opening,Arcade::NONE,Diff::NONE,Mode::NONE,puyoGameConstant::NO_WINNER,false};
    change_page(*signal.next_page);
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
        change_page(*signal.next_page);
}
