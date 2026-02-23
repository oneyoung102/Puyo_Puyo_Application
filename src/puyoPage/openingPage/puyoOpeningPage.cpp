#include <SFML/Graphics.hpp>
#include "../puyoPageSignal.hpp"
#include "puyoOpeningPage.hpp"

#include "../../puyoResources/printObject/puyoPrintObject.hpp"
#include "../../puyoResources/printText/puyoPrintTextFlash.hpp"
#include "../../puyoResources/puyoFileSystem.hpp"
#include "../../puyoResources/puyoPrinting.hpp"
#include "../../puyoResources/puyoImageConstant.hpp"
#include "../puyoLet.hpp"

using namespace std;
using namespace sf;
using namespace puyoImageConstant;

void puyoOpeningPage::let_end(){opening_end = true;}

puyoOpeningPage::puyoOpeningPage(puyoFileSystem& pfs)
    : SEGA_SPRITE(pfs.get_sprite(puyoFileSystem::Image::sega))
    , OPENING_SPRITE(pfs.get_sprite(puyoFileSystem::Image::opening))
{
    opening_printed = false;
    opening_end = false;
    pp.add_print_object(make_unique<puyoPrintObject>(SEGA_SPRITE,0,0,8000));
    ps.play_sound(pfs.get_buffer(puyoFileSystem::Sound::sega_intro));

    pl.allot_key((int)(Keyboard::Key::Enter),[this](){return let_end();});
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
        {
            signal.next_page = Page::game;//menu
            return signal;
        }
    }
    else if(pp.not_existed_print_object())
    {
        ps.play_music(pfs.get_music(puyoFileSystem::Music::main_menu));
        pp.add_print_object(make_unique<puyoPrintObject>(OPENING_SPRITE,0,0,-1));
        pp.add_print_text(make_unique<puyoPrintTextFlash>(
            TEXT_PRESS_ENTER_X,TEXT_PRESS_ENTER_Y,
            "Press Enter",
            pfs.get_font(),
            35,
            Color::White,
            Text::Style::Regular,
            -1,
            1200));
        opening_printed = true;
    }
    signal.next_page = Page::none;
    return signal;
}