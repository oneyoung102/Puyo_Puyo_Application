#pragma once

#include "puyoPos.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"
#include <SFML/Graphics.hpp>

namespace puyoEndingConstant
{
    const int TEXT_APPEAR_TICK = 300, BUTTON_APPEAR_TICK = 650;
    const POSf TEXT_WINNER_POS = puyoImageConstant::SCREEN_CENTER+POSf(0,-35);
    const int TEXT_WINNER_SIZE = 60;

    const POSf REPLAY_BUTTON_POS = puyoImageConstant::SCREEN_CENTER+POSf(-85, 70);
    const POSf TO_MENU_BUTTON_POS = puyoImageConstant::SCREEN_CENTER+POSf(85,70);
    const float REPLAY_BUTTON_SCALE = 1, TO_MENU_BUTTON_SCALE = 1;
}