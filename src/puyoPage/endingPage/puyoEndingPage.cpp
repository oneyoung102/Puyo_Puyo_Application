#include <SFML/Graphics.hpp>
#include "../puyoPageSignal.hpp"
#include "puyoEndingPage.hpp"

#include "../../puyoResources/puyoFileSystem.hpp"
#include "../../puyoResources/puyoPrinting.hpp"
#include "../../puyoResources/printObject/puyoPrintObject.hpp"
#include "../../puyoResources/printText/puyoPrintText.hpp"
#include "../../puyoResources/puyoFileSystem.hpp"
#include "../../puyoResources/puyoPrinting.hpp"
#include "../../puyoResources/puyoImageConstant.hpp"

#include "../puyoLet.hpp"
#include "../../puyoResources/printText/puyoPrintTextZoom.hpp"
#include <memory>

using namespace std;
using namespace sf;
using namespace puyoImageConstant;

void puyoEndingPage::let_end(){re_play = true;}

puyoEndingPage::puyoEndingPage(puyoFileSystem& pfs, int wpn, sf::Sprite capture_sprite, Play_mode pm)
{
    pp.add_print_object(make_unique<puyoPrintObject>(capture_sprite,0,0,-1));
    pp.add_print_object(make_unique<puyoPrintObject>(pfs.get_sprite(puyoFileSystem::Image::black_back),0,0,PRINT_IMMORTAL));
    win_player_num = wpn;
    play_mode = pm;

    proceed_count = 0;
    proceed_text_appear = 3000;
    proceed_button_appear = 6000;
    re_play = false;
}
puyoPageSignal puyoEndingPage::proceed_page(puyoFileSystem& pfs, RenderWindow& window)
{
    puyoPageSignal signal;
    ps.manage_all_sounds();
    pp.print_all_objects(window);
    pp.print_all_texts(window);
    pp.print_all_buttons(window);

    proceed_count = min(proceed_count+1,proceed_button_appear+1);
    if(proceed_count == proceed_text_appear)
    {
        string text = "";
        switch(play_mode)
        {
            case Play_mode::solo :
                text = "Game Over!";
                ps.play_sound(pfs.get_buffer(puyoFileSystem::Sound::lose));
                break;
            case Play_mode::dual :
                text = "Player"+to_string(win_player_num+1)+" WIN!!!";
                ps.play_sound(pfs.get_buffer(puyoFileSystem::Sound::victory));
                break;
            case Play_mode::bot :
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
        };   
        pp.add_print_text(make_unique<puyoPrintText>(
        TEXT_WINNER_X,TEXT_WINNER_Y,
        text,
        pfs.get_font(),
        60,
        Color::White,
        (Text::Style)(Text::Style::Underlined | Text::Style::Bold),
        PRINT_IMMORTAL));
    }
    else if(proceed_count == proceed_button_appear)
    {
        pp.add_print_button(make_unique<puyoPrintButton>( //임시//임시//임시//임시//임시//임시//임시//임시//임시
        pfs.get_sprite(puyoFileSystem::Image::puyo),
        pfs.get_sprite(puyoFileSystem::Image::puyo),
        re_play,
        TEXT_WINNER_X,TEXT_WINNER_Y+70,
        "Press Enter to Replay",
        pfs.get_font(),
        40,
        Color::Blue,
        Text::Style::Bold,
        PRINT_IMMORTAL));
        pl.allot_key((int)(Keyboard::Key::Enter),[this](){return let_end();});
    }
    if(re_play)
    {
        signal.win_player_num = -1;
        signal.next_page = Page::game;
    } 
    return signal;
}