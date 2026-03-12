#include <SFML/Graphics.hpp>
#include "puyoPage/pages/readyPage/puyoReadyConstant.hpp"
#include "puyoPage/puyoPageManager/puyoPageSignal.hpp"
#include "puyoReadyPage.hpp"

#include "puyoResources/puyoFileSystem.hpp"
#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

using namespace std;
using namespace sf;
using namespace puyoImageConstant;
using namespace puyoReadyConstant;

puyoReadyPage::puyoReadyPage(puyoFileSystem& pfs)
{
    gravity = -1,
    stay = -1;
    colors = -1;
    pp.add_print_object(make_unique<puyoPrintObject>(pfs.get_sprite(puyoFileSystem::Image::basic_back),0,0,puyoImageConstant::PRINT_IMMORTAL));
    ps.play_music(pfs.get_music(puyoFileSystem::Music::ready_page));
    pp.add_print_button(make_unique<puyoPrintButton>(
        pfs.get_sprite(puyoFileSystem::Image::button),
        button_cursor.get_select_status(buttonName::easy),
        SCREEN_X/2-240,SCREEN_Y/2,
        "Easy",
        pfs.get_font(),
        1.1,
        Color::White,
        Text::Style::Bold,
        PRINT_IMMORTAL));
    pp.add_print_button(make_unique<puyoPrintButton>(//임시임시임시임시임시임시임시임시임시임시임시임시임시임시임시임시임시
        pfs.get_sprite(puyoFileSystem::Image::button),
        button_cursor.get_select_status(buttonName::normal),
        SCREEN_X/2-90,SCREEN_Y/2,
        "normal",
        pfs.get_font(),
        1.1,
        Color::White,
        Text::Style::Bold,
        PRINT_IMMORTAL));
    pp.add_print_button(make_unique<puyoPrintButton>(
        pfs.get_sprite(puyoFileSystem::Image::button),
        button_cursor.get_select_status(buttonName::hard),
        SCREEN_X/2+60,SCREEN_Y/2,
        "Hard",
        pfs.get_font(),
        1.1,
        Color::White,
        Text::Style::Bold,
        PRINT_IMMORTAL));
    pp.add_print_button(make_unique<puyoPrintButton>(
        pfs.get_sprite(puyoFileSystem::Image::button),
        button_cursor.get_select_status(buttonName::back),
        SCREEN_X/2+240,SCREEN_Y/2,
        "Back",
        pfs.get_font(),
        0.9,
        Color::White,
        Text::Style::Bold,
        PRINT_IMMORTAL));
    pl.allot_key((int)(Keyboard::Key::Left),[this](){return button_cursor.let_choose_left();});
    pl.allot_key((int)(Keyboard::Key::Right),[this](){return button_cursor.let_choose_right();});
    pl.allot_key((int)(Keyboard::Key::Enter),[this](){return button_cursor.let_select();});
    convert_page = false;
}
puyoPageSignal puyoReadyPage::proceed_page(puyoFileSystem& pfs, RenderWindow& window)
{
    puyoPageSignal signal;
    pp.print_all_objects(window);
    pp.print_all_texts(window);
    pp.print_all_buttons(window);
    ps.manage_all_sounds();
    if(button_cursor.get_signal(puyoButtonCursorSignal::cursor))
    {
        ps.play_sound(pfs.get_buffer(puyoFileSystem::Sound::cursor));
        switch(button_cursor.get_selected_button())
        {
            case buttonName::easy :
                tie(gravity,stay,colors) = EASY_DIFF_SETTING;
                break;
            case buttonName::normal :
                tie(gravity,stay,colors) = NORMAL_DIFF_SETTING;
                break;
            case buttonName::hard :
                tie(gravity,stay,colors) = HARD_DIFF_SETTING;
                break;
            case buttonName::back :
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
        switch(button_cursor.get_selected_button())
        {
            case buttonName::back :
                signal.next_page = Page::menu;
                break;
            default :
                signal.next_page = Page::game;
                signal.gravity = gravity;
                signal.stay = stay;
                signal.colors = colors;
                break;
        };
    }
    return signal;
}