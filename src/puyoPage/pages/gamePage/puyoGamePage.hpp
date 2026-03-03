#pragma once

#include <SFML/Graphics.hpp>
#include "puyoPage/puyoPageManager/puyoPageSignal.hpp"
#include "puyoPage/pages/puyoPage.hpp"

#include "puyoPage/pages/gamePage/puyoPhase/puyoPhase.hpp"

#include "puyoResources/puyoFileSystem.hpp"

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
        puyoPhase phase;
        const Sprite PUYO_SPRITE, NUM_SPRITE, BOARD_SPRITE,COUNT_DOWN_BACK_SPRITE;
    public :
        puyoGamePage(puyoFileSystem& pfs, Play_mode play_mode, int condtion, int gravity, int stay, int colors);
        puyoPageSignal proceed_page(puyoFileSystem& pfs, sf::RenderWindow& window);
};