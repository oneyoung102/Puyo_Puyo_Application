#pragma once

#include <SFML/Graphics.hpp>
#include "../puyoPageSignal.hpp"
#include "../puyoPage.hpp"

#include "puyoPhasing.hpp"

#include "../../puyoResources/puyoFileSystem.hpp"

class puyoGamePage : public puyoPage
{
    private :
        enum class Ready_status
        {
            ready,
            start,
            play
        };
        Ready_status ready_status;
        puyoPhasing phase;
        const Sprite PUYO_SPRITE, NUM_SPRITE, BOARD_SPRITE,COUNT_DOWN_BACK_SPRITE;
    public :
        puyoGamePage(puyoFileSystem& pfs, Play_mode play_mode, int condtion, int gravity, int stay, int colors);
        puyoPageSignal proceed_page(puyoFileSystem& pfs, sf::RenderWindow& window);
};