#pragma once

#include <SFML/Graphics.hpp>
#include "puyoPage/pages/puyoButtonCursor.hpp"
#include "puyoPage/puyoPageManager/puyoPageSignal.hpp"
#include "puyoPage/pages/puyoPage.hpp"

#include "puyoResources/puyoFileSystem.hpp"

class puyoReadyPage : public puyoPage
{
    private :
        int gravity, stay, colors;
        enum class buttonName//임시
        {
            easy,
            normal,
            hard,
            back
        };
        puyoButtonCursor<1,4,buttonName> button_cursor;
        bool convert_page;
    public :
        puyoReadyPage(puyoFileSystem& pfs);
        puyoPageSignal proceed_page(puyoFileSystem& pfs, sf::RenderWindow& window);
};