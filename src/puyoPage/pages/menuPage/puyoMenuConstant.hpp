#pragma once

#include "puyoTool/puyoPos.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"
#include <SFML/Graphics.hpp>

namespace puyoMenuConstant
{
    const POSf TEXT_ARCADE_POS = puyoImageConstant::SCREEN_CENTER+POSf(0,-120);
    const int TEXT_ARCADE_SIZE = 58;
    const int TEXT_ARCADE_CYCLE = 115;

    const POSf SOLO_BUTTON_POS = puyoImageConstant::SCREEN_CENTER+POSf(-170,23);
    const POSf DUAL_BUTTON_POS = puyoImageConstant::SCREEN_CENTER+POSf(0,23);
    const POSf BOT_BUTTON_POS = puyoImageConstant::SCREEN_CENTER+POSf(170,23);
    const float DIFF_BUTTON_SCALE = 1.3;
}