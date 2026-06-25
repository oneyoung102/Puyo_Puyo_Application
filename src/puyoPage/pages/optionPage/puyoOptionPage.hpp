#pragma once

#include <SFML/Graphics.hpp>
#include "puyoPage/puyoButton/puyoButton.hpp"
#include "puyoPage/puyoPageManager/puyoPageSignal.hpp"
#include "puyoPage/pages/puyoPage.hpp"

#include "puyoResources/puyoFileSystem.hpp"

class puyoOptionPage : public puyoPage
{
    private :
        enum class buttonName
        {
            NONE,
            diff_dial,
            mode_dial,
            back,
            ready,
        };
        puyoButton<2,2,buttonName> buttons;
        puyoButton<1,3,Diff> dials_diff;
        puyoButton<1,7,Mode> dials_mode;
    public :
        puyoOptionPage(puyoFileSystem& pfs);
        puyoPageSignal proceed_page(puyoFileSystem& pfs, sf::RenderWindow& window);
};