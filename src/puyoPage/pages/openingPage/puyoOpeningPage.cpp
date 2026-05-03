#include <SFML/Graphics.hpp>
#include "puyoPage/pages/openingPage/puyoOpeningConstant.hpp"
#include "puyoPage/puyoPageManager/puyoPageSignal.hpp"
#include "puyoOpeningPage.hpp"

#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"
#include "puyoResources/puyoPrinting/printText/puyoPrintTextFlash.hpp"
#include "puyoResources/puyoFileSystem.hpp"
#include "puyoResources/puyoPrinting/puyoPrinting.hpp"
#include "puyoPage/puyoLet.hpp"

using namespace std;
using namespace sf;
using namespace puyoOpeningConstant;

void puyoOpeningPage::let_start(){convert_page = true;}

puyoOpeningPage::puyoOpeningPage(puyoFileSystem& pfs)
    : SEGA_SPRITE(pfs.get_sprite(puyoFileSystem::Image::sega))
    , OPENING_SPRITE(pfs.get_sprite(puyoFileSystem::Image::opening))
    , status(Status::init)
{}
puyoPageSignal puyoOpeningPage::proceed_page(puyoFileSystem& pfs, RenderWindow& window)
{
    puyoPageSignal signal;
    ps.manage_all_sounds();
    pp.print_all_objects(window);
    pp.print_all_texts(window);
    switch(status)
    {
        case Status::init :
            pp.add_print_object(make_unique<puyoPrintObject>(SEGA_SPRITE,SEGA_INTRO_TICK));
            ps.play_sound(pfs.get_buffer(puyoFileSystem::Sound::sega_intro));
            status = Status::intro;
            break;
        case Status::intro:
            if(!pp.object_back_alive())
            {
                ps.play_music(pfs.get_music(puyoFileSystem::Music::opening_page));
                pp.add_print_object(make_unique<puyoPrintObject>(OPENING_SPRITE));
                pp.add_print_text(make_unique<puyoPrintTextFlash>(
                    TEXT_PRESS_ENTER_POS,
                    "Press Enter",
                    pfs.get_font(),
                    TEXT_PRESS_ENTER_SIZE,
                    TEXT_PRESS_ENTER_CYCLE,
                    Color::White,
                    Text::Style::Regular));
                pl.allot_key(Keyboard::Key::Enter,FUNCFY(let_start));
                status = Status::opening;
            }
            break;
        case Status::opening:
            if(convert_page)
                signal.next_page = Page::menu;
            break;
    }
    return signal;
}