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
            
        case Page::game_1_player :
            curr_page = make_unique<puyoGamePage>(pfs,1);
            break;
        case Page::game_2_player :
            curr_page = make_unique<puyoGamePage>(pfs,2);
            break;
        case Page::game_with_bot :
            curr_page = make_unique<puyoGamePage>(pfs,2);//임시
            break;

        case Page::ending :
            curr_page = make_unique<puyoEndingPage>(pfs);
            break;
    };
}
puyoPageManager::puyoPageManager()
{
    curr_page = make_unique<puyoOpeningPage>(pfs);
}

void puyoPageManager::show_page(RenderWindow& window)
{
    while (auto event = window.pollEvent())//이벤트 처리
    {
        if (event->is<Event::Closed>())//닫힘 이벤트
            window.close();
        (curr_page->get_let()).detect_keyboard(event);
    }
    convert_page(curr_page->proceed_page(pfs,window));
}