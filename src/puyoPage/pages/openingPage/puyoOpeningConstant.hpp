#pragma once

#include "puyoTool/puyoPos.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"
#include <SFML/Graphics.hpp>

namespace puyoOpeningConstant
{
    const int SEGA_INTRO_TICK = 1050;
    const POSf TEXT_PRESS_ENTER_POS = puyoImageConstant::SCREEN_CENTER+POSf(0,20);
    const int TEXT_PRESS_ENTER_SIZE = 38;
    const int TEXT_PRESS_ENTER_CYCLE = 120;
}