#pragma once

#include <SFML/Graphics.hpp>
#include "puyoPage/puyoPageManager/puyoPageSignal.hpp"
#include "puyoPage/pages/puyoPage.hpp"

#include "puyoResources/puyoFileSystem.hpp"
#include "puyoPage/pages/puyoButtonCursor.hpp"

class puyoEndingPage : public puyoPage
{
    private :
        int win_player_num;
        Play_mode play_mode;

        int proceed_count;

        enum class buttonName{
            NONE,
            replay,
            to_menu
        };
        puyoButtonCursor<1,2,buttonName> button_cursor;
        bool convert_page;
    public :
        puyoEndingPage(puyoFileSystem& pfs, int wpn, sf::Sprite cs, Play_mode pm);
        puyoPageSignal proceed_page(puyoFileSystem& pfs,  sf::RenderWindow& window);
};