#pragma once

#include <array>
#include <tuple>
#include "puyoTool/puyoPos.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"
#include <SFML/Graphics.hpp>

namespace puyoGameConstant
{
    constexpr POSi BOARD_BASIC_SIZE = POSi(6,14);

    constexpr int PLAYPUYO_FOURWAYMOVE_TICK = 8;
    constexpr int PLAYPUYO_TURN_TICK = 7;
    constexpr int PLAYPUYO_DROP_GRAVITY_TICK = 3;
    constexpr int GRAVITY_TICK_THRESHOLD = 5; // 빠르고 느림을 구분

    constexpr int BOARD_FALL_GRAVITY_TICK = 6;
    constexpr int BOARD_COLOR_VANISH_TICK = 37;
    constexpr float VANISH_SOON_PROP = 0.85, VANISH_STAY_PROP = 0.7;
    constexpr int BOARD_OTHER_VANISH_TICK = 12;
    constexpr int BOARD_FLY_TICK = 39;

    constexpr auto PLAYPUYO_IN_BOARD_SPAWN_POS = POSf(2,0);

    constexpr float OBSTRUCT_PUYO_SPAWN_Y = -2;

    constexpr int OBSTRUCT_PUYO_MANY = 18, OBSTRUCT_PUYO_MID = 6;
    constexpr std::array<int,7> OBSTRUCT_VIEWER_UNIT = {1,6,30,180,360,720,1440};
    constexpr int OBSTRUCT_VIEWER_UPPER = 6;

    constexpr int DISPLAYED_NEXT_PUYO_COUNT = 2;

    constexpr int NO_WINNER = -1;
    constexpr int SCORE_UPPER = 1e8; // 이 스코어 미만

    constexpr int BOT_PENALTY = -100000;
    constexpr float MIN_LEARNING_RATE = 0.02, MIN_WEIGHT = 0.02;

    constexpr int CHARGED_COLOR_PUYO_WEIGHT = 100;

    //delay
    constexpr int PHASE_SET_TICK = 30;
    //밸런스
    constexpr int PUYO_VANISH_CONDITION = 4;
    constexpr int EASY_DIFF_GRAVITY_TICK = 43, EASY_DIFF_STAY_TICK = 77, EASY_DIFF_COLORS = 3;
    constexpr auto EASY_DIFF_SETTING = std::make_tuple(EASY_DIFF_GRAVITY_TICK,EASY_DIFF_STAY_TICK,EASY_DIFF_COLORS); // gravity,stay,colors
    constexpr int NORMAL_DIFF_GRAVITY_TICK = 36, NORMAL_DIFF_STAY_TICK = 57, NORMAL_DIFF_COLORS = 4;
    constexpr auto NORMAL_DIFF_SETTING = std::make_tuple(NORMAL_DIFF_GRAVITY_TICK,NORMAL_DIFF_STAY_TICK,NORMAL_DIFF_COLORS);
    constexpr int HARD_DIFF_GRAVITY_TICK = 27, HARD_DIFF_STAY_TICK = 38, HARD_DIFF_COLORS = 5;
    constexpr auto HARD_DIFF_SETTING = std::make_tuple(HARD_DIFF_GRAVITY_TICK,HARD_DIFF_STAY_TICK,HARD_DIFF_COLORS);

    constexpr int BASIC_OBSTRCUT_RATE = 70, BASIC_ALL_CLEARED_OBSTRUCT_PUYO = 30;
    constexpr std::array<int,20> CHAIN_BONUS = {0,0,8,16,32,64,96,128,160,192,224,256,288,320,352,384,416,448,480,512};
    constexpr std::array<int,12> LINK_BONUS = {0,0,0,0,0,2,3,4,5,6,7,10};// 11개 이상은 항상 10
    constexpr std::array<int,4> COLOR_BONUS = {2,4,6,8};

    constexpr int EASY_BOT_INIT_ACT_TICK = 20, NORMAL_BOT_INIT_ACT_TICK = 16, HARD_BOT_INIT_ACT_TICK = 10;
    //모드
    constexpr int BOMB_VANISH_TICK = 20;
    constexpr int BOMB_MAX_TICK = 3200;//0이면 안 됨
    constexpr float BOMB_UPDATED1 = 0.4, BOMB_UPDATED2 = 0.7, BOMB_UPDATED3 = 0.9;
    constexpr int BOMB_DISSOLVE_CHAIN = 3;
    constexpr int FREEZE_TICK = 650;
    constexpr int PROB_FREEZE_ONCE = 12, PROB_FREEZE_TWICE = 2;
    constexpr int CHARGE_CYCLE = 4;//4개 뉴뿌요마다 차지
    constexpr int SEED_CYCLE = 10, MAX_SEED_GAP = 2;
    constexpr int MIN_SEED_COUNT = 1, MAX_SEED_COUNT = 2;
    constexpr int WATERING_RANGE = 1, FLOWER_FLAME_HEIGHT = BOARD_BASIC_SIZE.y, FLOWER_DAISY_OBSTRUCT_RATE = 35;
    constexpr int FLOWER_DAISY_TICK = 2100, FLOWER_FLAME_TICK = 1800, FLOWER_SHILED_TICK = 2300;


    // printing
    constexpr int NOTICE_TICK = 260;
    constexpr int BLACK_BACK_TICK = 164;
    constexpr int TEXT_READY_SIZE = 60, TEXT_READY_TICK = 80;
    constexpr int TEXT_START_SIZE = 60, TEXT_START_TICK = 84;

    constexpr int TWO_BOARD_BREADTH = 386;
    constexpr std::array<POSf,2> PLAYER_BOARD_POS = {POSf(31,35),POSf(TWO_BOARD_BREADTH+31,35)};
    constexpr int BOARD_HEIGHT = 12;

    constexpr std::array<POSf,2> NEXT_PUYO_VIEWER_POS = {POSf(244,62),POSf(367,62)};
    constexpr int NEXT_PUYO_VIEWER_BREADTH = 36;

    constexpr int SCREEN_BAR_FROM_X = 302, SCREEN_BAR_FROM_Y = 60, SCREEN_BAR_TO_X = 38, SCREEN_BAR_TO_Y = 100;
    constexpr POSf SCREEN_BAR_FROM_POS = POSf(SCREEN_BAR_FROM_X,SCREEN_BAR_FROM_Y), SCREEN_BAR_TO_POS = POSf(SCREEN_BAR_TO_X,SCREEN_BAR_TO_Y);

    constexpr std::array<POSf,2> OBSTRUCT_VIEWER_POS = {POSf(31,2),POSf(TWO_BOARD_BREADTH+31,2)};

    constexpr std::array<POSf,2> SCORE_POS = {POSf(246,204),POSf(255,256)};

    constexpr std::array<POSf,2> TEXT_CHAIN_POS = {POSf(126,205),POSf(TWO_BOARD_BREADTH+126,205)};
    constexpr int TEXT_CHAIN_SIZE = 29, TEXT_CHAIN_TICK = 30;
    constexpr std::array<POSf,2> TEXT_ALL_CLEAR_POS = {POSf(126,241),POSf(TWO_BOARD_BREADTH+126,241)};
    constexpr int TEXT_ALL_CLEAR_SIZE = 31, TEXT_ALL_CLEAR_TICK = 90;
    //모드
    constexpr POSf TEXT_SPEED_UP_POS = {puyoImageConstant::SCREEN_X/2.0,310};
    constexpr int TEXT_SPEED_UP_SIZE = 38, TEXT_SPEED_UP_TICK = 66;
};