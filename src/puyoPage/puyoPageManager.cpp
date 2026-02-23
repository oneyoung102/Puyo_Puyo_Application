#include "puyoPageManager.hpp"
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
        case Page::none :
            break;
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
            curr_page = make_unique<puyoGamePage>(pfs,play_mode,gravity,colors);
            break;
        case Page::ending :
            curr_page = make_unique<puyoEndingPage>(pfs,win_player_num,capture_sprite);
            break;
    };
}
puyoPageManager::puyoPageManager()
    : capture_sprite(Sprite(capture_texture))
{
    next_page = Page::opening;
    play_mode = Play_mode::bot;
    gravity = 1800;
    colors = 4;
    win_player_num = -1;
}

void puyoPageManager::show_page(RenderWindow& window)
{
    convert_page(next_page);
    while (auto event = window.pollEvent())
    {
        if (event->is<Event::Closed>())
            window.close();
        curr_page->get_let().detect_keyboard(event);
    }
    window.clear();
    puyoPageSignal signal = curr_page->proceed_page(pfs, window);
    next_page = signal.next_page;
    if(next_page != Page::none)
    {
        if (signal.play_mode)
            play_mode = *signal.play_mode;
        if (signal.gravity)
            gravity = *signal.gravity;
        if (signal.colors)
            colors = *signal.colors;
        if (signal.win_player_num)
            win_player_num = *signal.win_player_num;
    }
    window.display();
    if (signal.request_capture && *signal.request_capture)
    {
        capture_texture = sf::Texture(window.getSize()); 
        capture_texture.update(window);
        capture_sprite.setTexture(capture_texture, true);
    }
}
