#pragma once

#include <array>
#include <tuple>
#include "puyoTool/puyoPos.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"
#include <SFML/Graphics.hpp>

namespace puyoGameConstant
{
    const POSi BOARD_BASIC_SIZE = POSi(6,12);

    const int PLAYPUYO_FOURWAYMOVE_TICK = 40;
    const int PLAYPUYO_TURN_TICK = 36;
    const int PLAYPUYO_DROP_GRAVITY_TICK = 15;
    const int GRAVITY_TICK_STANDARD = 25;

    const int BOARD_FALL_GRAVITY_TICK = 31;
    const int BOARD_BASIC_VANISH_TICK = 185;
    const float VANISH_SOON_PROP = 0.85, VANISH_STAY_PROP = 0.7;
    const int BOARD_OBSTRUCT_VANISH_TICK = 60;
    const int BOARD_FLY_TICK = 197;

    const POSf PLAYPUYO_IN_BOARD_SPAWN_POS = POSf(2,-0.9);

    const float OBSTRUCT_PUYO_SPAWN_Y = -2;

    const int OBSTRUCT_PUYO_MANY = 18, OBSTRUCT_PUYO_MID = 6;
    const std::array<int,7> OBSTRUCT_VIEWER_UNIT = {1,6,30,180,360,720,1440};
    const int OBSTRUCT_VIEWER_UPPER = 6;

    const int NO_WINNER = -1;

    //delay
    const int PHASE_SET_TICK = 150;
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
    const int BOMB_MAX_TICK = fmax(0,16000);//0이면 안 됨
    const int BOMB_UPDATED1 = 10000, BOMB_UPDATED2 = 5000, BOMB_UPDATED3 = 1600;
    const int BOMB_DISSOLVE_CHAIN = 3;


    // printing
    const int BLACK_BACK_TICK = 820;
    const int TEXT_READY_SIZE = 60, TEXT_READY_TICK = 400;
    const int TEXT_START_SIZE = 60, TEXT_START_TICK = 420;

    const int TWO_BOARD_BREADTH = 386;
    const std::array<POSf,2> PLAYER_BOARD_POS = {POSf(31,35),POSf(TWO_BOARD_BREADTH+31,35)};
    const int BOARD_HEIGHT = 12;

    const std::array<POSf,2> NEXT_PUYO_VIEWER_POS = {POSf(244,62),POSf(367,62)};
    const int NEXT_PUYO_VIEWER_BREADTH = 36;

    const int SCREEN_BAR_FROM_X = 302, SCREEN_BAR_FROM_Y = 60, SCREEN_BAR_TO_X = 38, SCREEN_BAR_TO_Y = 100;
    const POSf SCREEN_BAR_FROM_POS = POSf(SCREEN_BAR_FROM_X,SCREEN_BAR_FROM_Y), SCREEN_BAR_TO_POS = POSf(SCREEN_BAR_TO_X,SCREEN_BAR_TO_Y);

    const std::array<POSf,2> OBSTRUCT_VIEWER_POS = {POSf(31,2),POSf(TWO_BOARD_BREADTH+31,2)};

    const std::array<POSf,2> SCORE_POS = {POSf(246,204),POSf(255,256)};

    const std::array<POSf,2> TEXT_CHAIN_POS = {POSf(126,205),POSf(TWO_BOARD_BREADTH+126,205)};
    const int TEXT_CHAIN_SIZE = 29, TEXT_CHAIN_TICK = 150;
    const std::array<POSf,2> TEXT_ALL_CLEAR_POS = {POSf(126,241),POSf(TWO_BOARD_BREADTH+126,241)};
    const int TEXT_ALL_CLEAR_SIZE = 31, TEXT_ALL_CLEAR_TICK = 450;
    //모드
    const POSf TEXT_SPEED_UP_POS = {puyoImageConstant::SCREEN_X/2.0,310};
    const int TEXT_SPEED_UP_SIZE = 38, TEXT_SPEED_UP_TICK = 330;
};