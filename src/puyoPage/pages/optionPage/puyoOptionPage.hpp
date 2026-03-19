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
        enum class diffDialName
        {
            NONE,
            easy,
            normal,
            hard,
        };
        enum class modeDialName
        {
            NONE,
            basic,
        };
        puyoButtonCursor<2,2,buttonName> button_cursor;
        puyoButtonCursor<1,3,diffDialName> diff_dial_button_cursor;
        puyoButtonCursor<1,1,modeDialName> mode_dial_button_cursor;
        bool convert_page;
    public :
        puyoOptionPage(puyoFileSystem& pfs);
        puyoPageSignal proceed_page(puyoFileSystem& pfs, sf::RenderWindow& window);
};