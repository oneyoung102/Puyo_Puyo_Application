#include <SFML/Graphics.hpp>
#include "puyoPage/pages/puyoButtonCursor.hpp"
#include "puyoPage/puyoPageManager/puyoPageSignal.hpp"
#include "puyoMenuPage.hpp"
#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"
#include "puyoResources/puyoFileSystem.hpp"
#include "puyoResources/puyoPrinting/puyoPrinting.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

#include "puyoResources/puyoPrinting/printButton/puyoPrintButton.hpp"

#include <memory>

using namespace std;
using namespace sf;
using namespace puyoImageConstant;

puyoMenuPage::puyoMenuPage(puyoFileSystem& pfs)
{
    pp.add_print_object(make_unique<puyoPrintObject>(pfs.get_sprite(puyoFileSystem::Image::basic_back),0,0,-1));
    ps.play_music(pfs.get_music(puyoFileSystem::Music::menu_page));

    pp.add_print_button(make_unique<puyoPrintButton>(
        pfs.get_sprite(puyoFileSystem::Image::button),
        button_cursor.get_select_status(buttonName::dual),
        SCREEN_X/2,SCREEN_Y/2,
        "Dual",
        pfs.get_font(),
        1.3,
        Color::White,
        Text::Style::Bold,
        PRINT_IMMORTAL));
    pp.add_print_button(make_unique<puyoPrintButton>(
        pfs.get_sprite(puyoFileSystem::Image::button),
        button_cursor.get_select_status(buttonName::solo),
        SCREEN_X/2-170,SCREEN_Y/2,
        "Solo",
        pfs.get_font(),
        1.3,
        Color::White,
        Text::Style::Bold,
        PRINT_IMMORTAL));
    pp.add_print_button(make_unique<puyoPrintButton>(
        pfs.get_sprite(puyoFileSystem::Image::button),
        button_cursor.get_select_status(buttonName::bot),
        SCREEN_X/2+170,SCREEN_Y/2,
        "Bot",
        pfs.get_font(),
        1.3,
        Color::White,
        Text::Style::Bold,
        PRINT_IMMORTAL));
    pl.allot_key((int)(Keyboard::Key::Left),[this](){return button_cursor.let_choose_left();});
    pl.allot_key((int)(Keyboard::Key::Right),[this](){return button_cursor.let_choose_right();});
    pl.allot_key((int)(Keyboard::Key::Enter),[this](){return button_cursor.let_select();});
    convert_page = false;
}
puyoPageSignal puyoMenuPage::proceed_page(puyoFileSystem& pfs,RenderWindow& window)
{
    puyoPageSignal signal;
    pp.print_all_objects(window);
    pp.print_all_buttons(window);
    ps.manage_all_sounds();
    if(button_cursor.get_signal(puyoButtonCursorSignal::cursor))
    {
        ps.play_sound(pfs.get_buffer(puyoFileSystem::Sound::cursor));
        switch(button_cursor.get_selected_button())
        {
            case buttonName::solo :
                play_mode = Play_mode::solo;
                break;
            case buttonName::dual :
                play_mode = Play_mode::dual;
                break;
            case buttonName::bot :
                play_mode = Play_mode::bot;
                break;
        };
    }
    if(!convert_page)
    {
        convert_page = button_cursor.get_signal(puyoButtonCursorSignal::select);
        if(convert_page)
        {
            ps.play_sound(pfs.get_buffer(puyoFileSystem::Sound::select));
            pl.clear_allot();
        }
    }
    else if(ps.sounds_empty())
    {
        signal.next_page = Page::ready;
        signal.play_mode = this->play_mode;
    }
    return signal;
}