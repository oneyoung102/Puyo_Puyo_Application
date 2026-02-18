#include <SFML/Graphics.hpp>
#include "../puyoPageSignal.hpp"
#include "../puyoPage.hpp"
#include "puyoOpeningPage.hpp"

#include "../../puyoResources/printObject/puyoPrintObject.hpp"
#include "../../puyoResources/printText/puyoPrintTextFlash.hpp"
#include "../../puyoResources/puyoFileSystem.hpp"
#include "../../puyoResources/puyoPrinting.hpp"
#include "../../puyoResources/puyoImageConstant.hpp"
#include "../puyoLet.hpp"

using namespace std;
using namespace sf;
using namespace puyoImageConstant;

void puyoOpeningPage::let_end(){opening_end = true;}

puyoOpeningPage::puyoOpeningPage(puyoFileSystem& pfs)
    : SEGA_SPRITE(pfs.get_sprite(pfs.sega))
    , OPENING_SPRITE(pfs.get_sprite(pfs.opening))
{
    opening_printed = false;
    opening_end = false;
    pp.add_print_object(make_unique<puyoPrintObject>(SEGA_SPRITE,0,0,6000));
    pl.allot_key((int)(Keyboard::Key::Enter),[this](){return let_end();});
}
Page puyoOpeningPage::proceed_page(puyoFileSystem& pfs,RenderWindow& window)
{
    if(!pp.not_existed_print_object())
    {
        pp.print_all_objects(window);
        pp.print_all_texts(window);

        if(opening_printed && opening_end)
            return Page::game_2_player;
    }
    else if(!opening_printed)
    {
        pp.add_print_object(make_unique<puyoPrintObject>(OPENING_SPRITE,0,0,-1));
        pp.add_print_text(make_unique<puyoPrintTextFlash>(
            TEXT_PRESS_ENTER_X,TEXT_PRESS_ENTER_Y,
            "Press Enter",
            pfs.get_font(),
            35,
            Color::White,
            Text::Style::Bold,
            -1,
            1200));
        opening_printed = true;
    }
    return Page::none;
}