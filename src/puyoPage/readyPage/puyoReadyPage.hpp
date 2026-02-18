#pragma once

#include <SFML/Graphics.hpp>
#include "../puyoPageSignal.hpp"
#include "../puyoPage.hpp"

#include "../../puyoResources/puyoFileSystem.hpp"

class puyoReadyPage : public puyoPage
{
    private :
    public :
        puyoReadyPage(puyoFileSystem& pfs);
        Page proceed_page(puyoFileSystem& pfs, sf::RenderWindow& window);
};