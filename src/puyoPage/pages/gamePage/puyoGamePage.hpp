#pragma once

#include <SFML/Graphics.hpp>
#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoPage/puyoObjectSignal/puyoObjectSignalReceiver.hpp"
#include "puyoPage/puyoPageManager/puyoPageSignal.hpp"
#include "puyoPage/pages/puyoPage.hpp"

#include "puyoPage/pages/gamePage/puyoPhase/puyoPhase.hpp"

#include "puyoResources/puyoFileSystem.hpp"

class puyoGamePage : public puyoPage
{
    private :
        bool skip;
        void let_skip();
        enum class Status
        {
            init,
            notice,
            ready,
            start,
            play
        };
        Status status;
        puyoPhase phase;
        const sf::Sprite PUYO_SPRITE, NUM_SPRITE, BOARD_SPRITE, NOTICE_SPRITE, COUNT_DOWN_BACK_SPRITE;
        puyoObjectSignalReceiver<puyoBoardSignal,puyoFileSystem&,const puyoPlayer&> boardSignalReceiver;
        puyoObjectSignalReceiver<puyoPlayPuyoSignal,puyoFileSystem&> puyoSignalReceiver;
        puyoObjectSignalReceiver<puyoPlayerSignal,puyoFileSystem&> playerSignalReceiver;
        puyoObjectSignalReceiver<puyoModeSignal,puyoFileSystem&> modeSignalReceiver;
        void receive_signals(puyoFileSystem& pfs);
    public :
        puyoGamePage(puyoFileSystem& pfs, Arcade arcade, Diff diff, Mode mode);
        puyoPageSignal proceed_page(puyoFileSystem& pfs, sf::RenderWindow& window);
};