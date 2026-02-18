#pragma once

#include <SFML/Graphics.hpp>
#include "../puyoPageSignal.hpp"
#include "../puyoPage.hpp"

#include "puyoPlayer.hpp"
#include "puyoBoard.hpp"
#include "puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoPhasing.hpp"

#include "../../puyoResources/puyoFileSystem.hpp"

class puyoGamePage : public puyoPage
{
    private :
        int count_down, count_down_time;
        puyoPhasing phase;
        const Sprite PUYO_SPRITE, NUM_SPRITE, BOARD_SPRITE,COUNT_DOWN_BACK_SPRITE;
    public :
        puyoGamePage(puyoFileSystem& pfs, int player_count);
        Page proceed_page(puyoFileSystem& pfs, sf::RenderWindow& window);
};