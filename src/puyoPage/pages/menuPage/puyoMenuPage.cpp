#include <SFML/Graphics.hpp>
#include "puyoPage/pages/menuPage/puyoMenuConstant.hpp"
#include "puyoPage/puyoPageManager/puyoPageSignal.hpp"
#include "puyoMenuPage.hpp"
#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"
#include "puyoResources/puyoFileSystem.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"
#include "puyoResources/puyoPrinting/puyoPrinting.hpp"

#include "puyoResources/puyoPrinting/printButton/puyoPrintButton.hpp"
#include "puyoResources/puyoPrinting/printText/puyoPrintTextZoom.hpp"

#include <memory>

using namespace std;
using namespace sf;
using namespace puyoMenuConstant;

puyoMenuPage::puyoMenuPage(puyoFileSystem& pfs)
    : buttons(decltype(buttons)({{Arcade::solo,Arcade::duel,Arcade::bot}}))
{
    pp.add_print_object(make_unique<puyoPrintObject>(pfs.get_sprite(puyoFileSystem::Image::basic_back)));
    ps.play_music(pfs.get_music(puyoFileSystem::Music::menu_page));

    pp.add_print_text(make_unique<puyoPrintTextZoom>(
        TEXT_ARCADE_POS,
        "Select Arcade!!!",
        pfs.get_font(),
        TEXT_ARCADE_SIZE,
        TEXT_ARCADE_CYCLE_TICK,
        Color::Green));
    pp.add_print_button(make_unique<puyoPrintButton>(
        pfs.get_sprite(puyoFileSystem::Image::button),
        buttons.cursor.get_select_status(Arcade::solo),
        SOLO_BUTTON_POS,
        "Solo",
        pfs.get_font(),
        DIFF_BUTTON_SCALE));
    pp.add_print_button(make_unique<puyoPrintButton>(
        pfs.get_sprite(puyoFileSystem::Image::button),
        buttons.cursor.get_select_status(Arcade::duel),
        DUEL_BUTTON_POS,
        "Duel",
        pfs.get_font(),
        DIFF_BUTTON_SCALE));
    pp.add_print_button(make_unique<puyoPrintButton>(
        pfs.get_sprite(puyoFileSystem::Image::button),
        buttons.cursor.get_select_status(Arcade::bot),
        BOT_BUTTON_POS,
        "Bot",
        pfs.get_font(),
        DIFF_BUTTON_SCALE));
    pl.allot_key(Keyboard::Key::Left,FUNCFY(buttons.cursor.let_choose_left));
    pl.allot_key(Keyboard::Key::Right,FUNCFY(buttons.cursor.let_choose_right));
    pl.allot_key(Keyboard::Key::Enter,FUNCFY(buttons.cursor.let_select));
    pp.add_print_text(make_unique<puyoPrintText>(
        TEXT_KEY_NOTICE_POS,
        "Arrows : Move, Enter : Select",
        pfs.get_font(),
        TEXT_KEY_NOTICE_SIZE,
        Color::White,
        Text::Style::Regular));
    
    buttons.set_executes(ps, pl);
}
puyoPageSignal puyoMenuPage::proceed_page(puyoFileSystem& pfs,RenderWindow& window)
{
    puyoPageSignal signal;
    pp.print_all_objects(window);
    pp.print_all_buttons(window);
    pp.print_all_texts(window);
    ps.manage_all_sounds();
    buttons.receive_signals(pfs);

    if(!convert_page)
        convert_page = buttons.selected();
    else if(ps.sounds_empty())
    {
        signal.next_page = Page::option;
        signal.arcade = buttons.cursor.get_selected_button();
    }
    return signal;
}