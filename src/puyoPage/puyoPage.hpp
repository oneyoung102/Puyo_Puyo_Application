#pragma once

#include <SFML/Graphics.hpp>
#include "puyoPageSignal.hpp"

#include "../puyoResources/puyoFileSystem.hpp"
#include "../puyoResources/puyoPrinting.hpp"
#include "../puyoResources/puyoSounding.hpp"
#include "puyoLet.hpp"

class puyoPage
{
    protected :
        puyoLet pl;
        puyoPrinting pp;
        puyoSounding ps;
    public :
        puyoPage();
        virtual ~puyoPage() = default;
        virtual puyoPageSignal proceed_page(puyoFileSystem& pfs, sf::RenderWindow& window) = 0;
        puyoLet& get_let();
};