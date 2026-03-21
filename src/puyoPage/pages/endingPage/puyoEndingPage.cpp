#include <SFML/Graphics.hpp>
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include "puyoPage/puyoPageManager/puyoPageSignal.hpp"
#include "puyoEndingPage.hpp"

#include "puyoResources/puyoFileSystem.hpp"
#include "puyoResources/puyoPrinting/puyoPrinting.hpp"
#include "puyoResources/puyoPrinting/printObject/puyoPrintObject.hpp"
#include "puyoResources/puyoPrinting/printText/puyoPrintText.hpp"
#include "puyoResources/puyoFileSystem.hpp"
#include "puyoResources/puyoPrinting/puyoPrinting.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

#include "puyoPage/puyoLet.hpp"
#include <memory>

using namespace std;
using namespace sf;
using namespace puyoImageConstant;


puyoEndingPage::puyoEndingPage(puyoFileSystem& pfs, int wpn, sf::Sprite capture_sprite, Arcade pm)
    : button_cursor(puyoButtonCursor<1,2,buttonName>({{buttonName::replay,buttonName::to_menu}}))
{
    pp.add_print_object(make_unique<puyoPrintObject>(capture_sprite,0,0,PRINT_IMMORTAL));
    pp.add_print_object(make_unique<puyoPrintObject>(pfs.get_sprite(puyoFileSystem::Image::black_back),0,0,PRINT_IMMORTAL));
    win_player_num = wpn;
    play_mode = pm;

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

    proceed_count = min(proceed_count+1,6501);
    switch(proceed_count)
    {
        case 3000 : 
        {
            string text = "";
            switch(play_mode)
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
                TEXT_WINNER_X,TEXT_WINNER_Y,
                text,
                pfs.get_font(),
                60,
                Color::White,
                (Text::Style)(Text::Style::Underlined | Text::Style::Bold),
                PRINT_IMMORTAL));
            break;
        }
        case 6500:
        {
            pp.add_print_button(make_unique<puyoPrintButton>(
                pfs.get_sprite(puyoFileSystem::Image::button),
                button_cursor.get_select_status(buttonName::replay),
                REPLAY_BUTTON_X,REPLAY_BUTTON_Y,
                "Replay",
                pfs.get_font(),
                1,
                Color::White,
                Text::Style::Bold,
                PRINT_IMMORTAL));
            pp.add_print_button(make_unique<puyoPrintButton>(
                pfs.get_sprite(puyoFileSystem::Image::button),
                button_cursor.get_select_status(buttonName::to_menu),
                TO_MENU_BUTTON_X,TO_MENU_BUTTON_Y,
                "To Menu",
                pfs.get_font(),
                1,
                Color::White,
                Text::Style::Bold,
                PRINT_IMMORTAL));
            pl.allot_key((int)(Keyboard::Key::Enter),[this](){return button_cursor.let_select();});
            pl.allot_key((int)(Keyboard::Key::Left),[this](){return button_cursor.let_choose_left();});
            pl.allot_key((int)(Keyboard::Key::Right),[this](){return button_cursor.let_choose_right();});
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
            pl.clear_allot();
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