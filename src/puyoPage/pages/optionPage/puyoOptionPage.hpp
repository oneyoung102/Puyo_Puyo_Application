#pragma once

#include <SFML/Graphics.hpp>
#include "puyoPage/pages/puyoButtonCursor.hpp"
#include "puyoPage/puyoPageManager/puyoPageSignal.hpp"
#include "puyoPage/pages/puyoPage.hpp"

#include "puyoResources/puyoFileSystem.hpp"

class puyoOptionPage : public puyoPage
{
    private :
        enum class buttonName
        {
            NONE,
            diff_dial,
            mode_dial,
            back,
            ready,
        };
        puyoButtonCursor<2,2,buttonName> button_cursor;
        puyoButtonCursor<1,3,Diff> diff_dial_button_cursor;
        puyoButtonCursor<1,4,Mode> mode_dial_button_cursor;
    public :
        puyoOptionPage(puyoFileSystem& pfs);
        puyoPageSignal proceed_page(puyoFileSystem& pfs, sf::RenderWindow& window);
};