#pragma once

#include "puyoTool/puyoPos.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"
#include <SFML/Graphics.hpp>

namespace puyoMenuConstant
{
    constexpr POSf TEXT_ARCADE_POS = puyoImageConstant::SCREEN_CENTER+POSf(0,-120);
    constexpr int TEXT_ARCADE_SIZE = 58;
    constexpr int TEXT_ARCADE_CYCLE = 115;

    constexpr POSf SOLO_BUTTON_POS = puyoImageConstant::SCREEN_CENTER+POSf(-170,23);
    constexpr POSf duel_BUTTON_POS = puyoImageConstant::SCREEN_CENTER+POSf(0,23);
    constexpr POSf BOT_BUTTON_POS = puyoImageConstant::SCREEN_CENTER+POSf(170,23);
    constexpr float DIFF_BUTTON_SCALE = 1.3;
}