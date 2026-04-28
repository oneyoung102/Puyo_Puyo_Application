#pragma once

#include "puyoTool/puyoCast.hpp"
#include "puyoTool/puyoPos.hpp"
#include <array>

enum Direction : size_t
{
    DOWN = 0,
    UP = 1,
    RIGHT = 2,
    LEFT = 3
};
inline Direction operator~(Direction d)
{
    return static_cast<Direction>(CASTs(d) ^ 1);
}
inline const std::array<POSi, 4> DIR = {POSi(0, 1), POSi(0, -1), POSi(1, 0), POSi(-1, 0)};
