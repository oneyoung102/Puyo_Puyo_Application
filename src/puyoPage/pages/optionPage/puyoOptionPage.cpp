#include <SFML/Graphics.hpp>
#include "puyoPage/pages/optionPage/puyoOptionConstant.hpp"
#include "puyoPage/puyoPageManager/puyoPageSignal.hpp"
#include "puyoOptionPage.hpp"

#include "puyoResources/puyoFileSystem.hpp"
#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"
#include "puyoResources/puyoPrinting/printButton/puyoPrintButton.hpp"
#include "puyoResources/puyoPrinting/printButton/puyoPrintDialButton.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

using namespace std;
using namespace sf;
using namespace puyoImageConstant;
using namespace puyoOptionConstant;

puyoOptionPage::puyoOptionPage(puyoFileSystem& pfs)
    : button_cursor(puyoButtonCursor<2,2,buttonName>({{buttonName::diff_dial,buttonName::NONE}
                                                                ,{buttonName::back,buttonName::ready}}))
    , diff_dial_button_cursor(puyoButtonCursor<1,3,diffDialName>({{diffDialName::easy,diffDialName::normal,diffDialName::hard}}))
    , mode_dial_button_cursor(puyoButtonCursor<1,1,modeDialName>({{modeDialName::basic}}))
{
    pp.add_print_object(make_unique<puyoPrintObject>(pfs.get_sprite(puyoFileSystem::Image::basic_back),0,0,puyoImageConstant::PRINT_IMMORTAL));
    ps.play_music(pfs.get_music(puyoFileSystem::Music::option_page));
    pp.add_print_button(make_unique<puyoPrintDialButton>(
        pfs.get_sprite(puyoFileSystem::Image::easy_button),
        diff_dial_button_cursor.get_select_status(diffDialName::easy),
        button_cursor.get_select_status(buttonName::diff_dial),
        SCREEN_X/2,SCREEN_Y/2,
        "Easy",
        pfs.get_font(),
        1,
        Color::White,
        Text::Style::Bold,
        PRINT_IMMORTAL));
    pp.add_print_button(make_unique<puyoPrintDialButton>(
        pfs.get_sprite(puyoFileSystem::Image::normal_button),
        diff_dial_button_cursor.get_select_status(diffDialName::normal),
        button_cursor.get_select_status(buttonName::diff_dial),
        SCREEN_X/2,SCREEN_Y/2,
        "Normal",
        pfs.get_font(),
        1,
        Color::White,
        Text::Style::Bold,
        PRINT_IMMORTAL));
    pp.add_print_button(make_unique<puyoPrintDialButton>(
        pfs.get_sprite(puyoFileSystem::Image::hard_button),
        diff_dial_button_cursor.get_select_status(diffDialName::hard),
        button_cursor.get_select_status(buttonName::diff_dial),
        SCREEN_X/2,SCREEN_Y/2,
        "Hard",
        pfs.get_font(),
        1,
        Color::White,
        Text::Style::Bold,
        PRINT_IMMORTAL));
    pp.add_print_button(make_unique<puyoPrintButton>(
        pfs.get_sprite(puyoFileSystem::Image::button),
        button_cursor.get_select_status(buttonName::back),
        SCREEN_X/2-140,SCREEN_Y/2+150,
        "Back",
        pfs.get_font(),
        0.9,
        Color::White,
        Text::Style::Bold,
        PRINT_IMMORTAL));
    pp.add_print_button(make_unique<puyoPrintButton>(
        pfs.get_sprite(puyoFileSystem::Image::button),
        button_cursor.get_select_status(buttonName::ready),
        SCREEN_X/2+140,SCREEN_Y/2+150,
        "Ready",
        pfs.get_font(),
        0.9,
        Color::White,
        Text::Style::Bold,
        PRINT_IMMORTAL));
    pl.allot_key((int)(Keyboard::Key::Left),[this](){return button_cursor.let_choose_left();});
    pl.allot_key((int)(Keyboard::Key::Right),[this](){return button_cursor.let_choose_right();});
    pl.allot_key((int)(Keyboard::Key::Up),[this](){return button_cursor.let_choose_up();});
    pl.allot_key((int)(Keyboard::Key::Down),[this](){return button_cursor.let_choose_down();});
    pl.allot_key((int)(Keyboard::Key::Enter),[this](){return button_cursor.let_select();});
    convert_page = false;
}
puyoPageSignal puyoOptionPage::proceed_page(puyoFileSystem& pfs, RenderWindow& window)
{
    puyoPageSignal signal;
    pp.print_all_objects(window);
    pp.print_all_texts(window);
    pp.print_all_buttons(window);
    ps.manage_all_sounds();

    if(button_cursor.get_signal(puyoButtonCursorSignal::cursor))
        ps.play_sound(pfs.get_buffer(puyoFileSystem::Sound::cursor));
    if(!convert_page)
    {
        if(button_cursor.get_signal(puyoButtonCursorSignal::select))
        {
            pl.clear_allot();
            switch(button_cursor.get_selected_button())
            {
                case buttonName::back :
                    convert_page = true;
                    break;
                case buttonName::ready :
                    convert_page = true;
                    break;
                case buttonName::diff_dial :
                    pl.allot_key((int)(Keyboard::Key::Left),[this](){return diff_dial_button_cursor.let_choose_left();});
                    pl.allot_key((int)(Keyboard::Key::Right),[this](){return diff_dial_button_cursor.let_choose_right();});
                    pl.allot_key((int)(Keyboard::Key::Enter),[this](){return diff_dial_button_cursor.let_select();});
                    break;
                case buttonName::mode_dial :
                    pl.allot_key((int)(Keyboard::Key::Left),[this](){return mode_dial_button_cursor.let_choose_left();});
                    pl.allot_key((int)(Keyboard::Key::Right),[this](){return mode_dial_button_cursor.let_choose_right();});
                    pl.allot_key((int)(Keyboard::Key::Enter),[this](){return mode_dial_button_cursor.let_select();});
                    break;
                case buttonName::NONE :
                    break;
            }  
            ps.play_sound(pfs.get_buffer(puyoFileSystem::Sound::select));
        }
        if(diff_dial_button_cursor.get_signal(puyoButtonCursorSignal::select) || mode_dial_button_cursor.get_signal(puyoButtonCursorSignal::select))
        {
            pl.allot_key((int)(Keyboard::Key::Left),[this](){return button_cursor.let_choose_left();});
            pl.allot_key((int)(Keyboard::Key::Right),[this](){return button_cursor.let_choose_right();});
            pl.allot_key((int)(Keyboard::Key::Up),[this](){return button_cursor.let_choose_up();});
            pl.allot_key((int)(Keyboard::Key::Down),[this](){return button_cursor.let_choose_down();});
            pl.allot_key((int)(Keyboard::Key::Enter),[this](){return button_cursor.let_select();});
            ps.play_sound(pfs.get_buffer(puyoFileSystem::Sound::select));
        }
    }
    else if(ps.sounds_empty())
    {
        switch(button_cursor.get_selected_button())
        {
            case buttonName::back :
                signal.next_page = Page::menu;
                break;
            case buttonName::ready :
                switch(diff_dial_button_cursor.get_selected_button())
                {
                    case diffDialName::easy :
                        tie(signal.gravity,signal.stay,signal.colors) = EASY_DIFF_SETTING;
                        break;
                    case diffDialName::normal :
                        tie(signal.gravity,signal.stay,signal.colors) = NORMAL_DIFF_SETTING;
                        break;
                    case diffDialName::hard :
                        tie(signal.gravity,signal.stay,signal.colors) = HARD_DIFF_SETTING;
                        break;
                    case diffDialName::NONE :
                        break;
                }
                signal.next_page = Page::game;
                break;
            default :
                break;
        };
    }
    return signal;
}