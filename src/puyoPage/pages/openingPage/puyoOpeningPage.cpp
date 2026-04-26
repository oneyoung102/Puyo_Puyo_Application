#include <SFML/Graphics.hpp>
#include "puyoPage/puyoPageManager/puyoPageSignal.hpp"
#include "puyoOpeningPage.hpp"

#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"
#include "puyoResources/puyoPrinting/printText/puyoPrintTextFlash.hpp"
#include "puyoResources/puyoFileSystem.hpp"
#include "puyoResources/puyoPrinting/puyoPrinting.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"
#include "puyoPage/puyoLet.hpp"

using namespace std;
using namespace sf;
using namespace puyoImageConstant;

void puyoOpeningPage::let_start(){opening_end = true;}

puyoOpeningPage::puyoOpeningPage(puyoFileSystem& pfs)
    : SEGA_SPRITE(pfs.get_sprite(puyoFileSystem::Image::sega))
    , OPENING_SPRITE(pfs.get_sprite(puyoFileSystem::Image::opening))
{
    opening_printed = false;
    opening_end = false;
    pp.add_print_object(make_unique<puyoPrintObject>(SEGA_SPRITE,950));
    ps.play_sound(pfs.get_buffer(puyoFileSystem::Sound::sega_intro));
}
puyoPageSignal puyoOpeningPage::proceed_page(puyoFileSystem& pfs, RenderWindow& window)
{
    puyoPageSignal signal;
    ps.manage_all_sounds();
    pp.print_all_objects(window);
    pp.print_all_texts(window);
    if(opening_printed)
    {
        if(opening_end)
            signal.next_page = Page::menu;
    }
    else if(pp.print_objects_empty())
    {
        ps.play_music(pfs.get_music(puyoFileSystem::Music::opening_page));
        pp.add_print_object(make_unique<puyoPrintObject>(OPENING_SPRITE,PRINT_IMMORTAL));
        pp.add_print_text(make_unique<puyoPrintTextFlash>(
            TEXT_PRESS_ENTER_POS,
            "Press Enter",
            pfs.get_font(),
            38,
            Color::White,
            Text::Style::Regular,
            PRINT_IMMORTAL,
            120));
        opening_printed = true;
        pl.allot_key((int)(Keyboard::Key::Enter),[this](){return let_start();});
    }
    return signal;
}