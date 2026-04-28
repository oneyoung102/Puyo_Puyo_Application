#include <SFML/Graphics.hpp>
#include "puyoPage/pages/endingPage/puyoEndingConstant.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include "puyoPage/puyoPageManager/puyoPageSignal.hpp"
#include "puyoEndingPage.hpp"

#include "puyoResources/puyoFileSystem.hpp"
#include "puyoResources/puyoPrinting/puyoPrinting.hpp"
#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"
#include "puyoResources/puyoPrinting/printText/puyoPrintText.hpp"
#include "puyoResources/puyoFileSystem.hpp"
#include "puyoResources/puyoPrinting/puyoPrinting.hpp"

#include "puyoPage/puyoLet.hpp"
#include <memory>

using namespace std;
using namespace sf;
using namespace puyoEndingConstant;


puyoEndingPage::puyoEndingPage(puyoFileSystem& pfs, int win_player_num, sf::Sprite capture_sprite, Arcade arcade)
    : button_cursor(puyoButtonCursor<1,2,buttonName>({{buttonName::replay,buttonName::to_menu}}))
    , win_player_num(win_player_num)
    , arcade(arcade)
{
    pp.add_print_object(make_unique<puyoPrintObject>(capture_sprite));
    pp.add_print_object(make_unique<puyoPrintObject>(pfs.get_sprite(puyoFileSystem::Image::black_back)));
    proceed_count = 0;
    convert_page = false;
}
puyoPageSignal puyoEndingPage::proceed_page(puyoFileSystem& pfs, RenderWindow& window)
{
    puyoPageSignal signal;
    ps.manage_all_sounds();
    pp.print_all_objects(window);
    pp.print_all_texts(window);
    pp.print_all_buttons(window);

    proceed_count = min(proceed_count,BUTTON_APPEAR_TICK)+1;
    switch(proceed_count)
    {
        case TEXT_APPEAR_TICK : 
        {
            string text = "";
            switch(arcade)
            {
                case Arcade::solo :
                    text = "Game Over!";
                    ps.play_sound(pfs.get_buffer(puyoFileSystem::Sound::lose));
                    break;
                case Arcade::dual :
                    text = "Player"+to_string(win_player_num+1)+" WIN!!!";
                    ps.play_sound(pfs.get_buffer(puyoFileSystem::Sound::victory));
                    break;
                case Arcade::bot :
                    if(win_player_num == 0)
                    {
                        text = "You WIN!!!";
                        ps.play_sound(pfs.get_buffer(puyoFileSystem::Sound::victory));
                    }
                    else//봇이 이김
                    {
                        text = "Bot WIN!!!";
                        ps.play_sound(pfs.get_buffer(puyoFileSystem::Sound::lose));
                    }
                    break;
                case Arcade::NONE :
                    break;
            };   
            pp.add_print_text(make_unique<puyoPrintText>(
                TEXT_WINNER_POS,
                text,
                pfs.get_font(),
                TEXT_WINNER_SIZE,
                Color::White,
                (Text::Style)(Text::Style::Underlined | Text::Style::Bold)));
            break;
        }
        case BUTTON_APPEAR_TICK:
        {
            pp.add_print_button(make_unique<puyoPrintButton>(
                pfs.get_sprite(puyoFileSystem::Image::button),
                button_cursor.get_select_status(buttonName::replay),
                REPLAY_BUTTON_POS,
                "Replay",
                pfs.get_font(),
                REPLAY_BUTTON_SCALE));
            pp.add_print_button(make_unique<puyoPrintButton>(
                pfs.get_sprite(puyoFileSystem::Image::button),
                button_cursor.get_select_status(buttonName::to_menu),
                TO_MENU_BUTTON_POS,
                "To Menu",
                pfs.get_font(),
                TO_MENU_BUTTON_SCALE));
            pl.allot_key(Keyboard::Key::Enter,FUNCFY(button_cursor.let_select));
            pl.allot_key(Keyboard::Key::Left,FUNCFY(button_cursor.let_choose_left));
            pl.allot_key(Keyboard::Key::Right,FUNCFY(button_cursor.let_choose_right));
            break;
        }
        default :
            break;
    }
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
        signal.win_player_num = puyoGameConstant::NO_WINNER;
        switch(button_cursor.get_selected_button())
        {
            case buttonName::NONE :
                break;
            case buttonName::replay :
                signal.next_page = Page::game;
                break;
            case buttonName::to_menu :
                signal.next_page = Page::menu;
                break;
        };
    } 
    return signal;
}