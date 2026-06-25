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
    , buttons(decltype(buttons)({{buttonName::diff_dial, buttonName::mode_dial},
                                 {buttonName::back, buttonName::ready}}))
    ,  dials_diff(decltype(dials_diff)({{Diff::easy, Diff::normal, Diff::hard}},true))
    ,  dials_mode(decltype(dials_mode)({{Mode::basic,Mode::speed, Mode::bomb, Mode::frozen, Mode::charged, Mode::blocks, Mode::garden}},true))
{
    pp.add_print_object(make_unique<puyoPrintObject>(pfs.get_sprite(puyoFileSystem::Image::basic_back),puyoImageConstant::PRINT_IMMORTAL));
    ps.play_music(pfs.get_music(puyoFileSystem::Music::option_page));

    //난이도
    pp.add_print_button(make_unique<puyoPrintDialButton>(
        pfs.get_sprite(puyoFileSystem::Image::easy_button),
        dials_diff.cursor.get_select_status(Diff::easy),
        buttons.cursor.get_select_status(buttonName::diff_dial),
        DIFF_DIAL_BUTTON_POS,
        "Easy",
        pfs.get_font(),
        DIFF_DIAL_BUTTON_SCALE));
    pp.add_print_button(make_unique<puyoPrintDialButton>(
        pfs.get_sprite(puyoFileSystem::Image::normal_button),
        dials_diff.cursor.get_select_status(Diff::normal),
        buttons.cursor.get_select_status(buttonName::diff_dial),
        DIFF_DIAL_BUTTON_POS,
        "Normal",
        pfs.get_font(),
        DIFF_DIAL_BUTTON_SCALE));
    pp.add_print_button(make_unique<puyoPrintDialButton>(
        pfs.get_sprite(puyoFileSystem::Image::hard_button),
        dials_diff.cursor.get_select_status(Diff::hard),
        buttons.cursor.get_select_status(buttonName::diff_dial),
        DIFF_DIAL_BUTTON_POS,
        "Hard",
        pfs.get_font(),
        DIFF_DIAL_BUTTON_SCALE));
    
    //모드
    pp.add_print_button(make_unique<puyoPrintDialButton>(
        pfs.get_sprite(puyoFileSystem::Image::basic_button),
        dials_mode.cursor.get_select_status(Mode::basic),
        buttons.cursor.get_select_status(buttonName::mode_dial),
        MODE_DIAL_BUTTON_POS,
        "Basic",
        pfs.get_font(),
        MODE_DIAL_BUTTON_SCALE));
    pp.add_print_button(make_unique<puyoPrintDialButton>(
        pfs.get_sprite(puyoFileSystem::Image::speed_button),
        dials_mode.cursor.get_select_status(Mode::speed),
        buttons.cursor.get_select_status(buttonName::mode_dial),
        MODE_DIAL_BUTTON_POS,
        "Speed-Up",
        pfs.get_font(),
        MODE_DIAL_BUTTON_SCALE));
    pp.add_print_button(make_unique<puyoPrintDialButton>(//임시
        pfs.get_sprite(puyoFileSystem::Image::bomb_button),
        dials_mode.cursor.get_select_status(Mode::bomb),
        buttons.cursor.get_select_status(buttonName::mode_dial),
        MODE_DIAL_BUTTON_POS,
        "Bomb",
        pfs.get_font(),
        MODE_DIAL_BUTTON_SCALE));
    pp.add_print_button(make_unique<puyoPrintDialButton>(//임시
        pfs.get_sprite(puyoFileSystem::Image::basic_button),
        dials_mode.cursor.get_select_status(Mode::frozen),
        buttons.cursor.get_select_status(buttonName::mode_dial),
        MODE_DIAL_BUTTON_POS,
        "Frozen",
        pfs.get_font(),
        MODE_DIAL_BUTTON_SCALE));
    pp.add_print_button(make_unique<puyoPrintDialButton>(//임시
        pfs.get_sprite(puyoFileSystem::Image::basic_button),
        dials_mode.cursor.get_select_status(Mode::charged),
        buttons.cursor.get_select_status(buttonName::mode_dial),
        MODE_DIAL_BUTTON_POS,
        "Charged",
        pfs.get_font(),
        MODE_DIAL_BUTTON_SCALE));
    pp.add_print_button(make_unique<puyoPrintDialButton>(//임시
        pfs.get_sprite(puyoFileSystem::Image::basic_button),
        dials_mode.cursor.get_select_status(Mode::blocks),
        buttons.cursor.get_select_status(buttonName::mode_dial),
        MODE_DIAL_BUTTON_POS,
        "Blocks",
        pfs.get_font(),
        MODE_DIAL_BUTTON_SCALE));
    pp.add_print_button(make_unique<puyoPrintDialButton>(//임시
        pfs.get_sprite(puyoFileSystem::Image::basic_button),
        dials_mode.cursor.get_select_status(Mode::garden),
        buttons.cursor.get_select_status(buttonName::mode_dial),
        MODE_DIAL_BUTTON_POS,
        "Garden",
        pfs.get_font(),
        MODE_DIAL_BUTTON_SCALE));

    //
    pp.add_print_button(make_unique<puyoPrintButton>(
        pfs.get_sprite(puyoFileSystem::Image::button),
        buttons.cursor.get_select_status(buttonName::back),
        BACK_BUTTON_POS,
        "Back",
        pfs.get_font(),
        BACK_BUTTON_SCALE));
    pp.add_print_button(make_unique<puyoPrintButton>(
        pfs.get_sprite(puyoFileSystem::Image::button),
        buttons.cursor.get_select_status(buttonName::ready),
        READY_BUTTON_POS,
        "Ready",
        pfs.get_font(),
        READY_BUTTON_SCALE));
    pl.allot_key(Keyboard::Key::Left,FUNCFY(buttons.cursor.let_choose_left));
    pl.allot_key(Keyboard::Key::Right,FUNCFY(buttons.cursor.let_choose_right));
    pl.allot_key(Keyboard::Key::Up,FUNCFY(buttons.cursor.let_choose_up));
    pl.allot_key(Keyboard::Key::Down,FUNCFY(buttons.cursor.let_choose_down));
    pl.allot_key(Keyboard::Key::Enter,FUNCFY(buttons.cursor.let_select));
    pp.add_print_text(make_unique<puyoPrintText>(
        TEXT_KEY_NOTICE_POS,
        "Arrows : Move, Enter : Select",
        pfs.get_font(),
        TEXT_KEY_NOTICE_SIZE,
        Color::White,
        Text::Style::Regular));

    buttons.set_executes(ps, pl);
    dials_diff.set_executes(ps, pl);
    dials_mode.set_executes(ps, pl);
}
puyoPageSignal puyoOptionPage::proceed_page(puyoFileSystem &pfs,RenderWindow &window) {
    puyoPageSignal signal;
    pp.print_all_objects(window);
    pp.print_all_texts(window);
    pp.print_all_buttons(window);
    ps.manage_all_sounds();
    buttons.receive_signals(pfs);
    dials_diff.receive_signals(pfs);
    dials_mode.receive_signals(pfs);

    if(!convert_page)
    {
        if(buttons.selected())
        {
            switch (buttons.cursor.get_selected_button())
            {
                case buttonName::back:
                    convert_page = true;
                    break;
                case buttonName::ready:
                    convert_page = true;
                    break;
                case buttonName::diff_dial:
                    pl.allot_key(Keyboard::Key::Left, FUNCFY(dials_diff.cursor.let_choose_left));
                    pl.allot_key(Keyboard::Key::Right, FUNCFY(dials_diff.cursor.let_choose_right));
                    pl.allot_key(Keyboard::Key::Enter, FUNCFY(dials_diff.cursor.let_select));
                    pp.add_print_text(make_unique<puyoPrintTextZoom>(
                        DIFF_DIAL_BUTTON_POS+TEXT_SELECT_COMPEL_POS,
                        "Select Difficulty!",
                        pfs.get_font(),
                        TEXT_SELECT_COMPEL_SIZE,
                        TEXT_SELECT_COMPEL_TICK,
                        Color::Green));
                    break;
                case buttonName::mode_dial:
                    pl.allot_key(Keyboard::Key::Left, FUNCFY(dials_mode.cursor.let_choose_left));
                    pl.allot_key(Keyboard::Key::Right, FUNCFY(dials_mode.cursor.let_choose_right));
                    pl.allot_key(Keyboard::Key::Enter, FUNCFY(dials_mode.cursor.let_select));
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
        }
        else if(dials_diff.selected() || dials_mode.selected())
        {
            pl.allot_key(Keyboard::Key::Left, FUNCFY(buttons.cursor.let_choose_left));
            pl.allot_key(Keyboard::Key::Right, FUNCFY(buttons.cursor.let_choose_right));
            pl.allot_key(Keyboard::Key::Up, FUNCFY(buttons.cursor.let_choose_up));
            pl.allot_key(Keyboard::Key::Down, FUNCFY(buttons.cursor.let_choose_down));
            pl.allot_key(Keyboard::Key::Enter, FUNCFY(buttons.cursor.let_select));
            ps.play_sound(pfs.get_buffer(puyoFileSystem::Sound::cancel));
            pp.clear_text_back();
        }
    }
    else if (ps.sounds_empty())
    {
        switch (buttons.cursor.get_selected_button()) 
        {
            case buttonName::back:
                signal.next_page = Page::menu;
                break;
            case buttonName::ready:
                signal.diff = dials_diff.cursor.get_selected_button();
                signal.mode = dials_mode.cursor.get_selected_button();
                signal.next_page = Page::game;
                break;
            default:
                break;
        };
    }
    return signal;
}