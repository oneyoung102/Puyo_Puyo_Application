#pragma once

#include "puyoPos.hpp"
#include <SFML/Graphics.hpp>

namespace puyoImageConstant//화면을 구성하는 이미지 크기와 관련한 클래스
{
    //puyo_board.png
        const unsigned int SCREEN_X = 640, SCREEN_Y = 444;
        const sf::Vector2u SCREEN_SIZE = {SCREEN_X,SCREEN_Y};
        const POSf SCREEN_CENTER = {SCREEN_X/2.0,SCREEN_Y/2.0};
    //puyos.png
        const int PUYO_SIZE = 32;

        const float FUTURE_PUYO_ALPHA_VALUE = 0.7; //투명도

        const auto DROPPING_PUYO_POS = POSi(4,13);
        const auto GRAVITY_PUYO_POS = POSi(5,11);
        const auto VANISH_SOON_PUYO_POS = POSi(6,10), VANISH_STAY_PUYO_POS = POSi(0,12);
        const auto VANISH_OTHER_POS = POSi(5,10);//이미지 위치 

        const int SPAWN_SPOT_STATE_MAX = 5; 
        const auto SPAWN_SPOT_POS = POSi(11,12);  //이미지 위치 
        const int SPAWN_SPOT_CYCLE_TICK = 80;

        const auto OBSTRUCT_PUYO_POS = POSi(10,12);//이미지 위치 
        const auto OBSTRUCT_VIEWER_PUYO_POS = POSi(6,15); //방해 뿌요 뷰어에 사용되는 이미지
        
        const auto ENERGY_PUYO_POS = POSi(11,11);//이미지 위치 

        const auto BOMB_POS = POSi(12,15); //이미지 위치 ..12~15
        const auto BOMB_VANISH_POS = POSi(0,5);

    //puyo_num.png
        const auto NUM_SIZE = POSi(18,29);
    //Text
        const int TEXT_ZOOM_SIZE_PROP = 30, TEXT_ZOOM_CYCLE_PROP = 15;
    //button
        const int TEXT_SIZE_IN_BUTTON = 31;//5글자 기준 기본 텍스트 사이즈
    const int PRINT_IMMORTAL = -1;
};