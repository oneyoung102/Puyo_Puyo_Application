#pragma once

#include "puyoTool/puyoPos.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"
#include <SFML/Graphics.hpp>

namespace puyoEndingConstant
{
    constexpr int TEXT_APPEAR_TICK = 60, BUTTON_APPEAR_TICK = 130;
    constexpr POSf TEXT_WINNER_POS = puyoImageConstant::SCREEN_CENTER+POSf(0,-35);
    constexpr int TEXT_WINNER_SIZE = 60;

    constexpr POSf REPLAY_BUTTON_POS = puyoImageConstant::SCREEN_CENTER+POSf(-85, 70);
    constexpr POSf TO_MENU_BUTTON_POS = puyoImageConstant::SCREEN_CENTER+POSf(85,70);
    constexpr float REPLAY_BUTTON_SCALE = 1, TO_MENU_BUTTON_SCALE = 1;
}