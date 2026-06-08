#pragma once

#include "puyoTool/puyoPos.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"
#include <SFML/Graphics.hpp>

#include "puyoPage/pages/menuPage/puyoMenuConstant.hpp"

namespace puyoOptionConstant
{
    constexpr POSf DIFF_DIAL_BUTTON_POS = puyoImageConstant::SCREEN_CENTER+POSf(-130,5);
    constexpr float DIFF_DIAL_BUTTON_SCALE = 1;

    constexpr POSf MODE_DIAL_BUTTON_POS = puyoImageConstant::SCREEN_CENTER+POSf(130,5);
    constexpr float MODE_DIAL_BUTTON_SCALE = 1;

    constexpr POSf TEXT_KEY_NOTICE_POS = puyoMenuConstant::TEXT_KEY_NOTICE_POS;
    constexpr int TEXT_KEY_NOTICE_SIZE = puyoMenuConstant::TEXT_KEY_NOTICE_SIZE;

    constexpr POSf TEXT_SELECT_COMPEL_POS = POSf(0,-112);
    constexpr int TEXT_SELECT_COMPEL_SIZE = 32;
    constexpr int TEXT_SELECT_COMPEL_TICK = 26;

    constexpr POSf BACK_BUTTON_POS = puyoImageConstant::SCREEN_CENTER+POSf(-190,143);
    constexpr POSf READY_BUTTON_POS = puyoImageConstant::SCREEN_CENTER+POSf(190,143);
    constexpr float BACK_BUTTON_SCALE = 0.9, READY_BUTTON_SCALE = 0.9;
}