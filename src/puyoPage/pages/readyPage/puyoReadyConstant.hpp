#pragma once

#include <tuple>

namespace puyoReadyConstant
{
    const int EASY_DIFF_GRAVITY = 2170, EASY_DIFF_STAY = 2850, EASY_DIFF_COLORS = 3;
    const std::tuple<int,int,int> EASY_DIFF_SETTING = std::make_tuple(EASY_DIFF_GRAVITY,EASY_DIFF_STAY,EASY_DIFF_COLORS); // gravity,stay,colors
    const int NORMAL_DIFF_GRAVITY = 1800, NORMAL_DIFF_STAY = 2000, NORMAL_DIFF_COLORS = 4;
    const std::tuple<int,int,int> NORMAL_DIFF_SETTING = std::make_tuple(NORMAL_DIFF_GRAVITY,NORMAL_DIFF_STAY,NORMAL_DIFF_COLORS);
    const int HARD_DIFF_GRAVITY = 1350, HARD_DIFF_STAY = 1500, HARD_DIFF_COLORS = 5;
    const std::tuple<int,int,int> HARD_DIFF_SETTING = std::make_tuple(HARD_DIFF_GRAVITY,HARD_DIFF_STAY,HARD_DIFF_COLORS);
};