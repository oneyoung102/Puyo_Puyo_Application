#pragma once

#include <vector>

namespace puyoGameConstant
{
    const int PLAYPUYO_STAY_BONUS = 110;

    const int PLAYPUYO_LEFT_TICK = 400;
    const int PLAYPUYO_RIGHT_TICK = 400;
    const int PLAYPUYO_DOWN_TICK = 400;
    const int PLAYPUYO_UP_TICK = 400;
    const int PLAYPUYO_TURN_TICK = 360;
    const int PLAYPUYO_DROP_GRAVITY_TICK = 150;

    const int PLAYPUYO_LEFT_DISTANCE = 1;
    const int PLAYPUYO_RIGHT_DISTANCE = 1;
    const int PLAYPUYO_DOWN_DISTANCE = 1;
    const int PLAYPUYO_UP_DISTANCE = 1;
    const int PLAYPUYO_TURN_DEGREE = -90;
    const int PLAYPUYO_FALL_GRAVITY_DISTANCE = 1;

    const int BOARD_FALL_GRAVITY_TICK = 310;
    const int BOARD_BASIC_VANISH_TICK = 1500;
    const int BOARD_OBSTRUCT_VANISH_TICK = 600;
    const int BOARD_FLY_TICK = 1670;

    const float PLAYPUYO_IN_BOARD_SPAWN_X = 2;
    const float PLAYPUYO_IN_BOARD_SPAWN_Y = -0.9;

    const float OBSTRUCT_PUYO_SPAWN_Y = -2;

    const int OBSTRUCT_PUYO_MANY = 18;
    const int OBSTRUCT_PUYO_MID = 6;
    const std::vector<int> OBSTRUCT_PUYO_VIEWER_UNIT = {1,6,30,180,360,720,1440};

    const int NO_WINNER = -1;
};