#include <SFML/Graphics.hpp>
#include "puyoPage/pages/menuPage/puyoMenuConstant.hpp"
#include "puyoPage/pages/puyoButtonCursor.hpp"
#include "puyoPage/puyoPageManager/puyoPageSignal.hpp"
#include "puyoMenuPage.hpp"
#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"
#include "puyoResources/puyoFileSystem.hpp"
#include "puyoResources/puyoPrinting/puyoPrinting.hpp"

#include "puyoResources/puyoPrinting/printButton/puyoPrintButton.hpp"
#include "puyoResources/puyoPrinting/printText/puyoPrintTextZoom.hpp"

#include <memory>

using namespace std;
using namespace sf;
using namespace puyoMenuConstant;

puyoMenuPage::puyoMenuPage(puyoFileSystem& pfs)
    : button_cursor(puyoButtonCursor<1,3,Arcade>({{Arcade::solo,Arcade::duel,Arcade::bot}}))
{
    pp.add_print_object(make_unique<puyoPrintObject>(pfs.get_sprite(puyoFileSystem::Image::basic_back),-1));
    ps.play_music(pfs.get_music(puyoFileSystem::Music::menu_page));

    pp.add_print_text(make_unique<puyoPrintTextZoom>(
        TEXT_ARCADE_POS,
        "Select Arcade!!!",
        pfs.get_font(),
        TEXT_ARCADE_SIZE,
        TEXT_ARCADE_CYCLE,
        Color::Green));
    pp.add_print_button(make_unique<puyoPrintButton>(
        pfs.get_sprite(puyoFileSystem::Image::button),
        button_cursor.get_select_status(Arcade::solo),
        SOLO_BUTTON_POS,
        "Solo",
        pfs.get_font(),
        DIFF_BUTTON_SCALE));
    pp.add_print_button(make_unique<puyoPrintButton>(
        pfs.get_sprite(puyoFileSystem::Image::button),
        button_cursor.get_select_status(Arcade::duel),
        duel_BUTTON_POS,
        "duel",
        pfs.get_font(),
        DIFF_BUTTON_SCALE));
    pp.add_print_button(make_unique<puyoPrintButton>(
        pfs.get_sprite(puyoFileSystem::Image::button),
        button_cursor.get_select_status(Arcade::bot),
        BOT_BUTTON_POS,
        "Bot",
        pfs.get_font(),
        DIFF_BUTTON_SCALE));
    pl.allot_key(Keyboard::Key::Left,FUNCFY(button_cursor.let_choose_left));
    pl.allot_key(Keyboard::Key::Right,FUNCFY(button_cursor.let_choose_right));
    pl.allot_key(Keyboard::Key::Enter,FUNCFY(button_cursor.let_select));
}
puyoPageSignal puyoMenuPage::proceed_page(puyoFileSystem& pfs,RenderWindow& window)
{
    puyoPageSignal signal;
    pp.print_all_objects(window);
    pp.print_all_buttons(window);
    pp.print_all_texts(window);
    ps.manage_all_sounds();
    if(button_cursor.get_signal(puyoButtonCursorSignal::cursor))
        ps.play_sound(pfs.get_buffer(puyoFileSystem::Sound::cursor));
    if(!convert_page)
    {
        convert_page = button_cursor.get_signal(puyoButtonCursorSignal::select);
        if(convert_page)
        {
            ps.play_sound(pfs.get_buffer(puyoFileSystem::Sound::select));
            pl.clear();
        }
    }
    else if(ps.sounds_empty())
    {
        signal.next_page = Page::option;
        signal.arcade = button_cursor.get_selected_button();
    }
    return signal;
}