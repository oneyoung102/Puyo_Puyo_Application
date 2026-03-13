#pragma once

#include <SFML/Graphics.hpp>
#include "puyoPage/puyoPageManager/puyoPageSignal.hpp"
#include "puyoPage/pages/puyoPage.hpp"
#include "puyoResources/puyoFileSystem.hpp"
#include "puyoPage/pages/puyoButtonCursor.hpp"

class puyoMenuPage : public puyoPage
{
    private :
        Play_mode play_mode;
        enum class buttonName
        {
            NONE,
            solo,
            dual,
            bot
        };
        puyoButtonCursor<1,3,buttonName> button_cursor;
        bool convert_page;
    public :
        puyoMenuPage(puyoFileSystem& pfs);
        puyoPageSignal proceed_page(puyoFileSystem& pfs, sf::RenderWindow& window);
};