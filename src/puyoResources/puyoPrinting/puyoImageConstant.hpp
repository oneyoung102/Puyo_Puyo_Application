#pragma once

#include "puyoTool/puyoPos.hpp"
#include <SFML/Graphics.hpp>

namespace puyoImageConstant//화면을 구성하는 이미지 크기와 관련한 클래스
{
    //puyo_board.png
        constexpr unsigned int SCREEN_X = 640, SCREEN_Y = 444;
        constexpr sf::Vector2u SCREEN_SIZE = {SCREEN_X,SCREEN_Y};
        constexpr POSf SCREEN_CENTER = {SCREEN_X/2.0f,SCREEN_Y/2.0f};
    //puyos.png
        constexpr int PUYO_SIZE = 32;

        constexpr float FUTURE_PUYO_ALPHA_VALUE = 0.7; //투명도

        constexpr auto CHARGED_PUYO_POS = POSi(0,9);
        constexpr auto DROPPING_PUYO_POS = POSi(4,13);
        constexpr auto GRAVITY_PUYO_POS = POSi(5,11);
        constexpr auto VANISH_SOON_PUYO_POS = POSi(6,10), VANISH_STAY_PUYO_POS = POSi(0,12);
        constexpr auto VANISH_OTHER_POS = POSi(5,10);//이미지 위치 

        constexpr int SPAWN_SPOT_STATE_MAX = 5; 
        constexpr auto SPAWN_SPOT_POS = POSi(11,12);  //이미지 위치 
        constexpr int SPAWN_SPOT_CYCLE_TICK = 16;

        constexpr auto OBSTRUCT_PUYO_POS = POSi(10,12);//이미지 위치 
        constexpr auto OBSTRUCT_VIEWER_PUYO_POS = POSi(6,15); //방해 뿌요 뷰어에 사용되는 이미지
        
        constexpr auto ENERGY_PUYO_POS = POSi(11,11);//이미지 위치 

        constexpr auto BOMB_POS = POSi(12,15); //이미지 위치 ..12~15
        constexpr auto FROZEN_PUYO_POS = POSi(13,9); //13~15
        constexpr auto WALL_PUYO_POS = POSi(11,9);

    //puyo_num.png
        constexpr auto NUM_SIZE = POSi(18,29);
        constexpr int SCORE_INCREMENT_DELTA = 11;
    //Text
        constexpr int TEXT_ZOOM_SIZE_PROP = 30, TEXT_ZOOM_CYCLE_PROP = 15;
    //button
        constexpr int TEXT_SIZE_IN_BUTTON = 31;//5글자 기준 기본 텍스트 사이즈
    constexpr float BRIGHTNESS = 0.15;
    constexpr int PRINT_IMMORTAL = -1;
};