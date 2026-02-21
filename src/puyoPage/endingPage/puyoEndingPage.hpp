#pragma once

#include <SFML/Graphics.hpp>
#include "../puyoPageSignal.hpp"
#include "../puyoPage.hpp"

#include "../../puyoResources/puyoFileSystem.hpp"

class puyoEndingPage : public puyoPage
{
    private :
        int win_player_num;
        int proceed_count, proceed_count_max;//멕스 도달 시 메세지 출력

        bool re_game;
        void let_end();
    public :
        puyoEndingPage(puyoFileSystem& pfs, int wpn, sf::Sprite cs);
        puyoPageSignal proceed_page(puyoFileSystem& pfs,  sf::RenderWindow& window);
};