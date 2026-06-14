#pragma once

#include <SFML/Graphics.hpp>
#include "puyoPage/puyoButton/puyoButton.hpp"
#include "puyoPage/puyoPageManager/puyoPageSignal.hpp"
#include "puyoPage/pages/puyoPage.hpp"
#include "puyoResources/puyoFileSystem.hpp"

class puyoMenuPage : public puyoPage
{
    private :
        puyoButton<1,3,Arcade> buttons;
    public :
        puyoMenuPage(puyoFileSystem& pfs);
        puyoPageSignal proceed_page(puyoFileSystem& pfs, sf::RenderWindow& window);
};