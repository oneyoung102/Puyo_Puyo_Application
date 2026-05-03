#pragma once

#include <SFML/Graphics.hpp>
#include "puyoPage/puyoPageManager/puyoPageSignal.hpp"
#include "puyoPage/pages/puyoPage.hpp"
#include "puyoResources/puyoFileSystem.hpp"

class puyoOpeningPage : public puyoPage
{
    private :
        enum class Status
        {
            init,
            intro,
            opening
        };
        Status status;
        const sf::Sprite SEGA_SPRITE, OPENING_SPRITE;
        void let_start();
    public :
        puyoOpeningPage(puyoFileSystem& pfs);
        puyoPageSignal proceed_page(puyoFileSystem& pfs, sf::RenderWindow& window);
};