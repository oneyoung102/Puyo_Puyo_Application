#pragma once

#include <vector>
#include <tuple>

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
    const float VANISH_SOON_PROP = 0.85, VANISH_STAY_PROP = 0.7;
    const int BOARD_OBSTRUCT_VANISH_TICK = 600;
    const int BOARD_FLY_TICK = 1670;

    const float PLAYPUYO_IN_BOARD_SPAWN_X = 2;
    const float PLAYPUYO_IN_BOARD_SPAWN_Y = -0.9;

    const float OBSTRUCT_PUYO_SPAWN_Y = -2;

    const int OBSTRUCT_PUYO_MANY = 18;
    const int OBSTRUCT_PUYO_MID = 6;
    const std::vector<int> OBSTRUCT_PUYO_VIEWER_UNIT = {1,6,30,180,360,720,1440};

    const int NO_WINNER = -1;

    //난이도
    const int PUYO_VANISH_CONDITION = 4;
    const int EASY_DIFF_GRAVITY = 2170, EASY_DIFF_STAY = 2850, EASY_DIFF_COLORS = 3;
    const std::tuple<int,int,int> EASY_DIFF_SETTING = std::make_tuple(EASY_DIFF_GRAVITY,EASY_DIFF_STAY,EASY_DIFF_COLORS); // gravity,stay,colors
    const int NORMAL_DIFF_GRAVITY = 1800, NORMAL_DIFF_STAY = 2000, NORMAL_DIFF_COLORS = 4;
    const std::tuple<int,int,int> NORMAL_DIFF_SETTING = std::make_tuple(NORMAL_DIFF_GRAVITY,NORMAL_DIFF_STAY,NORMAL_DIFF_COLORS);
    const int HARD_DIFF_GRAVITY = 1350, HARD_DIFF_STAY = 1500, HARD_DIFF_COLORS = 5;
    const std::tuple<int,int,int> HARD_DIFF_SETTING = std::make_tuple(HARD_DIFF_GRAVITY,HARD_DIFF_STAY,HARD_DIFF_COLORS);
    //모드
    const int BOMB_VANISH_TICK = 1000;
    const int BOMB_MAX_TICK = 160000;//0이면 안 됨
    const int BOMB_UPDATED1 = 100000, BOMB_UPDATED2 = 50000, BOMB_UPDATED3 = 16000;
    const int BOMB_DISSOLVE_CHAIN = 3;
};