#include "puyoOptionPage.hpp"
#include "puyoPage/pages/optionPage/puyoOptionConstant.hpp"
#include "puyoPage/puyoPageManager/puyoPageSignal.hpp"
#include <SFML/Graphics.hpp>

#include "puyoResources/puyoFileSystem.hpp"
#include "puyoResources/puyoPrinting/printButton/puyoPrintButton.hpp"
#include "puyoResources/puyoPrinting/printButton/puyoPrintDialButton.hpp"
#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"
#include "puyoResources/puyoPrinting/printText/puyoPrintTextZoom.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

using namespace std;
using namespace sf;
using namespace puyoImageConstant;
using namespace puyoOptionConstant;

puyoOptionPage::puyoOptionPage(puyoFileSystem &pfs)
    : puyoPage()
    , button_cursor(decltype(button_cursor)({{buttonName::diff_dial, buttonName::mode_dial},
                                                                    {buttonName::back, buttonName::ready}}))
    ,  diff_dial_button_cursor(decltype(diff_dial_button_cursor)({{Diff::easy, Diff::normal, Diff::hard}},true))
    ,  mode_dial_button_cursor(decltype(mode_dial_button_cursor)({{Mode::basic,Mode::speed,Mode::bomb,Mode::frozen, Mode::charged, Mode::blocks}},true))
{
    pp.add_print_object(make_unique<puyoPrintObject>(pfs.get_sprite(puyoFileSystem::Image::basic_back),puyoImageConstant::PRINT_IMMORTAL));
    ps.play_music(pfs.get_music(puyoFileSystem::Music::option_page));

    //난이도
    pp.add_print_button(make_unique<puyoPrintDialButton>(
        pfs.get_sprite(puyoFileSystem::Image::easy_button),
        diff_dial_button_cursor.get_select_status(Diff::easy),
        button_cursor.get_select_status(buttonName::diff_dial),
        DIFF_DIAL_BUTTON_POS,
        "Easy",
        pfs.get_font(),
        DIFF_DIAL_BUTTON_SCALE));
    pp.add_print_button(make_unique<puyoPrintDialButton>(
        pfs.get_sprite(puyoFileSystem::Image::normal_button),
        diff_dial_button_cursor.get_select_status(Diff::normal),
        button_cursor.get_select_status(buttonName::diff_dial),
        DIFF_DIAL_BUTTON_POS,
        "Normal",
        pfs.get_font(),
        DIFF_DIAL_BUTTON_SCALE));
    pp.add_print_button(make_unique<puyoPrintDialButton>(
        pfs.get_sprite(puyoFileSystem::Image::hard_button),
        diff_dial_button_cursor.get_select_status(Diff::hard),
        button_cursor.get_select_status(buttonName::diff_dial),
        DIFF_DIAL_BUTTON_POS,
        "Hard",
        pfs.get_font(),
        DIFF_DIAL_BUTTON_SCALE));
    
    //모드
    pp.add_print_button(make_unique<puyoPrintDialButton>(
        pfs.get_sprite(puyoFileSystem::Image::basic_button),
        mode_dial_button_cursor.get_select_status(Mode::basic),
        button_cursor.get_select_status(buttonName::mode_dial),
        MODE_DIAL_BUTTON_POS,
        "Basic",
        pfs.get_font(),
        MODE_DIAL_BUTTON_SCALE));
    pp.add_print_button(make_unique<puyoPrintDialButton>(
        pfs.get_sprite(puyoFileSystem::Image::speed_button),
        mode_dial_button_cursor.get_select_status(Mode::speed),
        button_cursor.get_select_status(buttonName::mode_dial),
        MODE_DIAL_BUTTON_POS,
        "Speed-Up",
        pfs.get_font(),
        MODE_DIAL_BUTTON_SCALE));
    pp.add_print_button(make_unique<puyoPrintDialButton>(//임시
        pfs.get_sprite(puyoFileSystem::Image::bomb_button),
        mode_dial_button_cursor.get_select_status(Mode::bomb),
        button_cursor.get_select_status(buttonName::mode_dial),
        MODE_DIAL_BUTTON_POS,
        "Bomb",
        pfs.get_font(),
        MODE_DIAL_BUTTON_SCALE));
    pp.add_print_button(make_unique<puyoPrintDialButton>(//임시
        pfs.get_sprite(puyoFileSystem::Image::basic_button),
        mode_dial_button_cursor.get_select_status(Mode::frozen),
        button_cursor.get_select_status(buttonName::mode_dial),
        MODE_DIAL_BUTTON_POS,
        "Frozen",
        pfs.get_font(),
        MODE_DIAL_BUTTON_SCALE));
    pp.add_print_button(make_unique<puyoPrintDialButton>(//임시
        pfs.get_sprite(puyoFileSystem::Image::basic_button),
        mode_dial_button_cursor.get_select_status(Mode::charged),
        button_cursor.get_select_status(buttonName::mode_dial),
        MODE_DIAL_BUTTON_POS,
        "Charged",
        pfs.get_font(),
        MODE_DIAL_BUTTON_SCALE));
    pp.add_print_button(make_unique<puyoPrintDialButton>(//임시
        pfs.get_sprite(puyoFileSystem::Image::basic_button),
        mode_dial_button_cursor.get_select_status(Mode::blocks),
        button_cursor.get_select_status(buttonName::mode_dial),
        MODE_DIAL_BUTTON_POS,
        "Blocks",
        pfs.get_font(),
        MODE_DIAL_BUTTON_SCALE));

    //
    pp.add_print_button(make_unique<puyoPrintButton>(
        pfs.get_sprite(puyoFileSystem::Image::button),
        button_cursor.get_select_status(buttonName::back),
        BACK_BUTTON_POS,
        "Back",
        pfs.get_font(),
        BACK_BUTTON_SCALE));
    pp.add_print_button(make_unique<puyoPrintButton>(
        pfs.get_sprite(puyoFileSystem::Image::button),
        button_cursor.get_select_status(buttonName::ready),
        READY_BUTTON_POS,
        "Ready",
        pfs.get_font(),
        READY_BUTTON_SCALE));
    pl.allot_key(Keyboard::Key::Left,FUNCFY(button_cursor.let_choose_left));
    pl.allot_key(Keyboard::Key::Right,FUNCFY(button_cursor.let_choose_right));
    pl.allot_key(Keyboard::Key::Up,FUNCFY(button_cursor.let_choose_up));
    pl.allot_key(Keyboard::Key::Down,FUNCFY(button_cursor.let_choose_down));
    pl.allot_key(Keyboard::Key::Enter,FUNCFY(button_cursor.let_select));
    pp.add_print_text(make_unique<puyoPrintText>(
        TEXT_KEY_NOTICE_POS,
        "Arrows : Move, Enter : Select",
        pfs.get_font(),
        TEXT_KEY_NOTICE_SIZE,
        Color::White,
        Text::Style::Regular));
}
puyoPageSignal puyoOptionPage::proceed_page(puyoFileSystem &pfs,RenderWindow &window) {
    puyoPageSignal signal;
    pp.print_all_objects(window);
    pp.print_all_texts(window);
    pp.print_all_buttons(window);
    ps.manage_all_sounds();

    if(button_cursor.get_signal(puyoButtonCursorSignal::cursor)
        || diff_dial_button_cursor.get_signal(puyoButtonCursorSignal::cursor)
        || mode_dial_button_cursor.get_signal(puyoButtonCursorSignal::cursor))
        ps.play_sound(pfs.get_buffer(puyoFileSystem::Sound::cursor));
    if(!convert_page)
    {
        if(button_cursor.get_signal(puyoButtonCursorSignal::select))
        {
            pl.clear();
            switch (button_cursor.get_selected_button())
            {
                case buttonName::back:
                    convert_page = true;
                    break;
                case buttonName::ready:
                    convert_page = true;
                    break;
                case buttonName::diff_dial:
                    pl.allot_key(Keyboard::Key::Left, FUNCFY(diff_dial_button_cursor.let_choose_left));
                    pl.allot_key(Keyboard::Key::Right, FUNCFY(diff_dial_button_cursor.let_choose_right));
                    pl.allot_key(Keyboard::Key::Enter, FUNCFY(diff_dial_button_cursor.let_select));
                    pp.add_print_text(make_unique<puyoPrintTextZoom>(
                        DIFF_DIAL_BUTTON_POS+TEXT_SELECT_COMPEL_POS,
                        "Select Difficulty!",
                        pfs.get_font(),
                        TEXT_SELECT_COMPEL_SIZE,
                        TEXT_SELECT_COMPEL_TICK,
                        Color::Green));
                    break;
                case buttonName::mode_dial:
                    pl.allot_key(Keyboard::Key::Left, FUNCFY(mode_dial_button_cursor.let_choose_left));
                    pl.allot_key(Keyboard::Key::Right, FUNCFY(mode_dial_button_cursor.let_choose_right));
                    pl.allot_key(Keyboard::Key::Enter, FUNCFY(mode_dial_button_cursor.let_select));
                    pp.add_print_text(make_unique<puyoPrintTextZoom>(
                        MODE_DIAL_BUTTON_POS+TEXT_SELECT_COMPEL_POS,
                        "Select Mode!",
                        pfs.get_font(),
                        TEXT_SELECT_COMPEL_SIZE,
                        TEXT_SELECT_COMPEL_TICK,
                        Color::Green));
                    break;
                case buttonName::NONE:
                    break;
            }
            ps.play_sound(pfs.get_buffer(puyoFileSystem::Sound::select));
        }
        else if(diff_dial_button_cursor.get_signal(puyoButtonCursorSignal::select)
                || mode_dial_button_cursor.get_signal(puyoButtonCursorSignal::select))
        {
            pl.allot_key(Keyboard::Key::Left, FUNCFY(button_cursor.let_choose_left));
            pl.allot_key(Keyboard::Key::Right, FUNCFY(button_cursor.let_choose_right));
            pl.allot_key(Keyboard::Key::Up, FUNCFY(button_cursor.let_choose_up));
            pl.allot_key(Keyboard::Key::Down, FUNCFY(button_cursor.let_choose_down));
            pl.allot_key(Keyboard::Key::Enter, FUNCFY(button_cursor.let_select));
            ps.play_sound(pfs.get_buffer(puyoFileSystem::Sound::cancel));
            pp.clear_text_back();
        }
    }
    else if (ps.sounds_empty())
    {
        switch (button_cursor.get_selected_button()) 
        {
            case buttonName::back:
                signal.next_page = Page::menu;
                break;
            case buttonName::ready:
                signal.diff = diff_dial_button_cursor.get_selected_button();
                signal.mode = mode_dial_button_cursor.get_selected_button();
                signal.next_page = Page::game;
                break;
            default:
                break;
        };
    }
    return signal;
}