#pragma once

#include <SFML/Graphics.hpp>
#include "puyoPage/puyoPageManager/puyoPageSignal.hpp"
#include "puyoPage/pages/puyoPage.hpp"

#include "puyoResources/puyoFileSystem.hpp"

class puyoEndingPage : public puyoPage
{
    private :
        int win_player_num;
        int proceed_count, proceed_text_appear, proceed_button_appear;

        Play_mode play_mode;
        bool re_play;
        void let_end();
    public :
        puyoEndingPage(puyoFileSystem& pfs, int wpn, sf::Sprite cs, Play_mode pm);
        puyoPageSignal proceed_page(puyoFileSystem& pfs,  sf::RenderWindow& window);
};