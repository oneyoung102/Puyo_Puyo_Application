#pragma once

#include <SFML/Graphics.hpp>
#include "puyoPageSignal.hpp"
#include "puyoPage.hpp"
#include "../puyoResources/puyoFileSystem.hpp"
#include "puyoLet.hpp"

#include <memory>

class puyoPageManager
{
    private : 
        puyoFileSystem pfs;
        std::unique_ptr<puyoPage> curr_page;
        void convert_page(Page p);
    public :
        puyoPageManager();
        void show_page(sf::RenderWindow& window);
};