#pragma once

#include "puyoTool/puyoPos.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"
#include <SFML/Graphics.hpp>

namespace puyoOptionConstant
{
    constexpr POSf DIFF_DIAL_BUTTON_POS = puyoImageConstant::SCREEN_CENTER-POSf(130,5);
    constexpr float DIFF_DIAL_BUTTON_SCALE = 1;

    constexpr POSf MODE_DIAL_BUTTON_POS = puyoImageConstant::SCREEN_CENTER+POSf(130,-5);
    constexpr float MODE_DIAL_BUTTON_SCALE = 1;

    constexpr POSf BACK_BUTTON_POS = puyoImageConstant::SCREEN_CENTER+POSf(-190,153);
    constexpr POSf READY_BUTTON_POS = puyoImageConstant::SCREEN_CENTER+POSf(190,153);
    constexpr float BACK_BUTTON_SCALE = 0.9, READY_BUTTON_SCALE = 0.9;
}