#pragma once

#include <SFML/Graphics.hpp>
#include "puyoPage/puyoPageManager/puyoPageSignal.hpp"

#include "puyoResources/puyoFileSystem.hpp"
#include "puyoResources/puyoPrinting/puyoPrinting.hpp"
#include "puyoResources/puyoSounding/puyoSounding.hpp"
#include "puyoPage/puyoKeyBoard/puyoLet.hpp"

class puyoPage
{
    protected :
        puyoLet pl;
        puyoPrinting pp;
        puyoSounding ps;
        bool convert_page;
    public :
        puyoPage();
        virtual ~puyoPage() = default;
        virtual puyoPageSignal proceed_page(puyoFileSystem& pfs, sf::RenderWindow& window) = 0;
        puyoLet& refer_let();
};