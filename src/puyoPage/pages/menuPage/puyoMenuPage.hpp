#pragma once

#include <SFML/Graphics.hpp>
#include "puyoPage/puyoPageManager/puyoPageSignal.hpp"
#include "puyoPage/pages/puyoPage.hpp"
#include "puyoResources/puyoFileSystem.hpp"
#include "puyoPage/pages/puyoButtonCursor.hpp"

class puyoMenuPage : public puyoPage
{
    private :
        puyoButtonCursor<1,3,Arcade> button_cursor;
    public :
        puyoMenuPage(puyoFileSystem& pfs);
        puyoPageSignal proceed_page(puyoFileSystem& pfs, sf::RenderWindow& window);
};