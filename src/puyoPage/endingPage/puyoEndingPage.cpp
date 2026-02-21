#include <SFML/Graphics.hpp>
#include "../puyoPageSignal.hpp"
#include "../puyoPage.hpp"
#include "puyoEndingPage.hpp"

#include "../../puyoResources/puyoFileSystem.hpp"
#include "../../puyoResources/puyoPrinting.hpp"
#include "../../puyoResources/printObject/puyoPrintObject.hpp"
#include "../../puyoResources/printText/puyoPrintText.hpp"
#include "../../puyoResources/puyoFileSystem.hpp"
#include "../../puyoResources/puyoPrinting.hpp"
#include "../../puyoResources/puyoImageConstant.hpp"

#include "../puyoLet.hpp"
#include <memory>

using namespace std;
using namespace sf;
using namespace puyoImageConstant;

void puyoEndingPage::let_end(){re_game = true;}

puyoEndingPage::puyoEndingPage(puyoFileSystem& pfs, int wpn, sf::Sprite capture_sprite)
{
    pp.add_print_object(make_unique<puyoPrintObject>(capture_sprite,0,0,-1));
    pp.add_print_object(make_unique<puyoPrintObject>(pfs.get_sprite(puyoFileSystem::Image::black_back),0,0,-1));
    win_player_num = wpn;
    proceed_count = 0;
    proceed_count_max = 3000;
    re_game = false;
    pl.allot_key((int)(Keyboard::Key::Enter),[this](){return let_end();});
}
puyoPageSignal puyoEndingPage::proceed_page(puyoFileSystem& pfs, RenderWindow& window)
{
    puyoPageSignal signal;
    ps.manage_all_sounds();
    pp.print_all_objects(window);
    pp.print_all_texts(window);
    if(proceed_count <= proceed_count_max)
    {
        ++proceed_count;
        if(proceed_count == proceed_count_max)
        {
            ps.play_sound(pfs.get_buffer(puyoFileSystem::Sound::victory));
            if(win_player_num == -1)//이긴 사람 없음 == 솔로 플레이
                pp.add_print_text(make_unique<puyoPrintText>(
                    TEXT_WINNER_X,TEXT_WINNER_Y,
                    "Game Over!",
                    pfs.get_font(),
                    60,
                    Color::White,
                    (Text::Style)(Text::Style::Underlined | Text::Style::Bold),
                    -1));
            else
                pp.add_print_text(make_unique<puyoPrintText>(
                    TEXT_WINNER_X,TEXT_WINNER_Y,
                    "Player"+to_string(win_player_num+1)+" WIN!!!",
                    pfs.get_font(),
                    60,
                    Color::White,
                    (Text::Style)(Text::Style::Underlined | Text::Style::Bold),
                    -1));
        }
    }
    if(re_game)
    {
        signal.win_player_num = -1;
        signal.next_page = Page::game;
        return signal;
    } 
    signal.next_page = Page::none;
    return signal;
}