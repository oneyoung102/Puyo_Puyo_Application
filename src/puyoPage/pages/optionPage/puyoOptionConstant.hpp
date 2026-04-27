#pragma once

#include "puyoPos.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"
#include <SFML/Graphics.hpp>

namespace puyoOptionConstant
{
    const POSf DIFF_DIAL_BUTTON_POS = puyoImageConstant::SCREEN_CENTER-POSf(130,5);
    const float DIFF_DIAL_BUTTON_SCALE = 1;

    const POSf MODE_DIAL_BUTTON_POS = puyoImageConstant::SCREEN_CENTER+POSf(130,-5);
    const float MODE_DIAL_BUTTON_SCALE = 1;

    const POSf BACK_BUTTON_POS = puyoImageConstant::SCREEN_CENTER+POSf(-190,153);
    const POSf READY_BUTTON_POS = puyoImageConstant::SCREEN_CENTER+POSf(190,153);
    const float BACK_BUTTON_SCALE = 0.9, READY_BUTTON_SCALE = 0.9;
}