#pragma once

#include <SFML/Graphics.hpp>
#include "../puyoPageSignal.hpp"
#include "../puyoPage.hpp"
#include "../../puyoResources/puyoFileSystem.hpp"

class puyoMenuPage : public puyoPage
{
    private :
        Play_mode play_mode;
        bool declined;
        void let_decline_solo();
        void let_decline_dual();
        void let_decline_bot();
    public :
        puyoMenuPage(puyoFileSystem& pfs);
        puyoPageSignal proceed_page(puyoFileSystem& pfs, sf::RenderWindow& window);
};