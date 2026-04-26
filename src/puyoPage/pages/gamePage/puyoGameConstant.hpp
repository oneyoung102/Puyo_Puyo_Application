#pragma once

#include <vector>
#include <tuple>
#include "puyoPos.hpp"

namespace puyoGameConstant
{

    const int PLAYPUYO_FOURWAYMOVE_TICK = 40;
    const int PLAYPUYO_TURN_TICK = 36;
    const int PLAYPUYO_DROP_GRAVITY_TICK = 15;
    const int GRAVITY_TICK_STANDARD = 25;

    const int BOARD_FALL_GRAVITY_TICK = 31;
    const int BOARD_BASIC_VANISH_TICK = 150;
    const float VANISH_SOON_PROP = 0.85, VANISH_STAY_PROP = 0.7;
    const int BOARD_OBSTRUCT_VANISH_TICK = 60;
    const int BOARD_FLY_TICK = 167;

    const POS PLAYPUYO_IN_BOARD_SPAWN_POS = POS(2,-0.9);

    const float OBSTRUCT_PUYO_SPAWN_Y = -2;

    const int OBSTRUCT_PUYO_MANY = 18;
    const int OBSTRUCT_PUYO_MID = 6;
    const std::vector<int> OBSTRUCT_PUYO_VIEWER_UNIT = {1,6,30,180,360,720,1440};

    const int NO_WINNER = -1;

    //난이도
    const int PUYO_VANISH_CONDITION = 4;
    const int EASY_DIFF_GRAVITY = 217, EASY_DIFF_STAY = 385, EASY_DIFF_COLORS = 3;
    const std::tuple<int,int,int> EASY_DIFF_SETTING = std::make_tuple(EASY_DIFF_GRAVITY,EASY_DIFF_STAY,EASY_DIFF_COLORS); // gravity,stay,colors
    const int NORMAL_DIFF_GRAVITY = 180, NORMAL_DIFF_STAY = 285, NORMAL_DIFF_COLORS = 4;
    const std::tuple<int,int,int> NORMAL_DIFF_SETTING = std::make_tuple(NORMAL_DIFF_GRAVITY,NORMAL_DIFF_STAY,NORMAL_DIFF_COLORS);
    const int HARD_DIFF_GRAVITY = 135, HARD_DIFF_STAY = 190, HARD_DIFF_COLORS = 5;
    const std::tuple<int,int,int> HARD_DIFF_SETTING = std::make_tuple(HARD_DIFF_GRAVITY,HARD_DIFF_STAY,HARD_DIFF_COLORS);
    //모드
    const int BOMB_VANISH_TICK = 100;
    const int BOMB_MAX_TICK = 16000;//0이면 안 됨
    const int BOMB_UPDATED1 = 10000, BOMB_UPDATED2 = 5000, BOMB_UPDATED3 = 1600;
    const int BOMB_DISSOLVE_CHAIN = 3;
};