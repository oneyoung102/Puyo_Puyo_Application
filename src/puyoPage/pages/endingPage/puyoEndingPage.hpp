#pragma once

#include <SFML/Graphics.hpp>
#include "puyoPage/puyoPageManager/puyoPageSignal.hpp"
#include "puyoPage/pages/puyoPage.hpp"

#include "puyoResources/puyoFileSystem.hpp"
#include "puyoPage/pages/puyoButtonCursor.hpp"

class puyoEndingPage : public puyoPage
{
    private :
        const int win_player_num;
        const Arcade arcade;
        int proceed_count;

        enum class buttonName
        {
            NONE,
            replay,
            to_menu
        };
        puyoButtonCursor<1,2,buttonName> button_cursor;
    public :
        puyoEndingPage(puyoFileSystem& pfs, int win_player_num, sf::Sprite capture_sprite, Arcade arcade);
        puyoPageSignal proceed_page(puyoFileSystem& pfs,  sf::RenderWindow& window);
};