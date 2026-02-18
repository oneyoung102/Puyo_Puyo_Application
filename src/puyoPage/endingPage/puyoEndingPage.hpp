#pragma once

#include <SFML/Graphics.hpp>
#include "../puyoPageSignal.hpp"
#include "../puyoPage.hpp"

#include "../../puyoResources/puyoFileSystem.hpp"

class puyoEndingPage : public puyoPage
{
    private :
    public :
        puyoEndingPage(puyoFileSystem& pfs);
        Page proceed_page(puyoFileSystem& pfs,  sf::RenderWindow& window);
};