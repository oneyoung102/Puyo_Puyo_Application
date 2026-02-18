#pragma once

#include <SFML/Graphics.hpp>
#include "../puyoPageSignal.hpp"
#include "../puyoPage.hpp"
#include "../../puyoResources/puyoFileSystem.hpp"

class puyoOpeningPage : public puyoPage
{
    private :
        bool opening_printed, opening_end;
        const Sprite SEGA_SPRITE, OPENING_SPRITE;
        void let_end();
    public :
        puyoOpeningPage(puyoFileSystem& pfs);
        Page proceed_page(puyoFileSystem& pfs, sf::RenderWindow& window);
};