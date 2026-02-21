#pragma once

#include <SFML/Graphics.hpp>
#include "../puyoPageSignal.hpp"
#include "../puyoPage.hpp"
#include "../../puyoResources/puyoFileSystem.hpp"

class puyoMenuPage : public puyoPage
{
    private :
    public :
        puyoMenuPage(puyoFileSystem& pfs);
        puyoPageSignal proceed_page(puyoFileSystem& pfs, sf::RenderWindow& window);
};