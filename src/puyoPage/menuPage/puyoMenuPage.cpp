#include <SFML/Graphics.hpp>
#include "../puyoPageSignal.hpp"
#include "puyoMenuPage.hpp"
#include "../../puyoResources/printObject/puyoPrintObject.hpp"
#include "../../puyoResources/puyoFileSystem.hpp"
#include "../../puyoResources/puyoPrinting.hpp"
#include "../../puyoResources/puyoImageConstant.hpp"

#include "../../puyoResources/printText/puyoPrintTextZoom.hpp"

#include <memory>

using namespace std;
using namespace sf;
using namespace puyoImageConstant;

void puyoMenuPage::let_decline_solo(){play_mode = Play_mode::solo; declined = true;}
void puyoMenuPage::let_decline_dual(){play_mode = Play_mode::dual; declined = true;}
void puyoMenuPage::let_decline_bot(){play_mode = Play_mode::bot; declined = true;}

puyoMenuPage::puyoMenuPage(puyoFileSystem& pfs)
{
    pp.add_print_object(make_unique<puyoPrintObject>(pfs.get_sprite(puyoFileSystem::Image::basic_back),0,0,-1));
    ps.play_music(pfs.get_music(puyoFileSystem::Music::character_select));

    pp.add_print_text(make_unique<puyoPrintTextZoom>( //임시//임시//임시//임시//임시//임시//임시//임시//임시
        SCREEN_X/2,SCREEN_Y/2,
        "1 : solo\n2 : dual\n3 : bot",
        pfs.get_font(),
        50,
        Color::Blue,
        Text::Style::Bold,
        -1,
        500));
    declined = false;
    pl.allot_key((int)(Keyboard::Key::Num1),[this](){return let_decline_solo();});//임시//임시//임시//임시//임시
    pl.allot_key((int)(Keyboard::Key::Num2),[this](){return let_decline_dual();});
    pl.allot_key((int)(Keyboard::Key::Num3),[this](){return let_decline_bot();});
}
puyoPageSignal puyoMenuPage::proceed_page(puyoFileSystem& pfs,RenderWindow& window)
{
    puyoPageSignal signal;
    pp.print_all_objects(window);
    pp.print_all_texts(window);
    ps.manage_all_sounds();
    if(declined)
    {
        signal.next_page = Page::game;
        signal.play_mode = this->play_mode;
    }
    else
        signal.next_page = Page::none;
    return signal;
}