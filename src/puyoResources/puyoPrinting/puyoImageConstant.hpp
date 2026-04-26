#pragma once

#include <vector>
#include "puyoPos.hpp"

#include <SFML/Graphics.hpp>

namespace puyoImageConstant//화면을 구성하는 이미지 크기와 관련한 클래스
{
    //puyo_board.png
        //gamePage
        const unsigned int SCREEN_X = 640, SCREEN_Y = 444;
        const sf::Vector2u SCREEN_SIZE = {SCREEN_X,SCREEN_Y};
        const sf::Vector2f SCREEN_CENTER = {SCREEN_X/2.0,SCREEN_Y/2.0};
        const std::vector<POS> PLAYER_BOARD_POS = {POS(31,35),POS(386+31,35)};
        const int BOARD_HEIGHT = 12;

        const std::vector<POS> PLAYER_NEXT_PUYO_VIEWER_POS = {POS(244,62),POS(367,62)};
        const int NEXT_PUYO_VIEWER_BREADTH = 36;

        const int SCREEN_BAR_FROM_X = 302, SCREEN_BAR_FROM_Y = 60, SCREEN_BAR_TO_X = 38, SCREEN_BAR_TO_Y = 100;
        const POS SCREEN_BAR_FROM_POS = POS(SCREEN_BAR_FROM_X,SCREEN_BAR_FROM_Y), SCREEN_BAR_TO_POS = POS(SCREEN_BAR_TO_X,SCREEN_BAR_TO_Y);

        const std::vector<POS> PLAYER_OBSTRUCT_VIEWER_POS = {POS(31,2),POS(386+31,2)};

    //puyos.png
        //gamePage
        const int PUYO_SIZE = 32;

        const float FUTURE_PUYO_ALPHA_VALUE = 0.7;

        const int DROPPING_PUYO_X = 4, DROPPING_PUYO_Y = 13;
        const int GRAVITY_PUYO_X = 5, GRAVITY_PUYO_Y = 11;
        const int VANISH_SOON_PUYO_X = 6, VANISH_SOON_PUYO_Y = 10, VANISH_STAY_PUYO_X = 0, VANISH_STAY_PUYO_Y = 12;
        const int VANISH_OTHER_X = 5, VANISH_OTHER_Y = 10;//이미지 위치 

        const int SPAWN_SPOT_STATE_MAX = 5; 
        const int SPAWN_SPOT_STATE_X = 11, SPAWN_SPOT_STATE_Y = 12;  //이미지 위치 

        const int OBSTRUCT_PUYO_X = 10, OBSTRUCT_PUYO_Y = 12;//이미지 위치 
        const int OBSTRUCT_PUYO_VIEWER_X = 6, OBSTRUCT_PUYO_VIEWER_Y = 15; //방해 뿌요 뷰어에 사용되는 이미지
        
        const int ENERGY_PUYO_X = 11, ENERGY_PUYO_Y = 11;//이미지 위치 

        const int BOMB_X = 12, BOMB_Y = 15; //이미지 위치 ..12~15
        const int BOMB_VANISH_X = 0, BOMB_VANISH_Y = 5;

    //puyo_num.png
        //gamePage
        const int NUM_SIZE_X = 18, NUM_SIZE_Y = 29;
        const std::vector<POS> PLAYER_SCORE_POS = {POS(246,204),POS(255,256)};

    //Text
        //gamePage
        const std::vector<sf::Vector2f> TEXT_PLAYER_CHAIN_POS = {{126,205},{386+126,205}};
        const std::vector<sf::Vector2f> TEXT_PLAYER_ALL_CLEAR_POS = {{126,241},{386+126,241}};
            //speed up mode
            const sf::Vector2f TEXT_SPEED_UP_POS = {SCREEN_X/2.0,310};
        //openingPage
        const sf::Vector2f TEXT_PRESS_ENTER_POS = {SCREEN_X/2.0,SCREEN_Y/2.0+20};
        //menuPage
        const sf::Vector2f TEXT_ARCADE_POS = {SCREEN_X/2.0f, SCREEN_Y/2.0f-120};
        //endingPage
        const sf::Vector2f TEXT_WINNER_POS = {SCREEN_X/2.0f, SCREEN_Y/2.0f-35};
    
    //button
        const int TEXT_SIZE_IN_BUTTON = 31;//5글자 기준 기본 텍스트 사이즈
        //menuPage
        const sf::Vector2f SOLO_BUTTON_POS = {SCREEN_X/2.0f-170, SCREEN_Y/2.0f+23};
        const sf::Vector2f DUAL_BUTTON_POS = {SCREEN_X/2.0f, SCREEN_Y/2.0f+23};
        const sf::Vector2f BOT_BUTTON_POS = {SCREEN_X/2.0f+170, SCREEN_Y/2.0f+23};
        //openingPage
        //optionPage
        const sf::Vector2f DIFF_DIAL_BUTTON_POS = {SCREEN_X / 2.0f-130, SCREEN_Y/2.0f-5};
        const sf::Vector2f MODE_DIAL_BUTTON_POS = {SCREEN_X / 2.0f+130, SCREEN_Y/2.0f-5};

        const sf::Vector2f BACK_BUTTON_POS = {SCREEN_X / 2.0f - 190, SCREEN_Y / 2.0f + 153};
        const sf::Vector2f READY_BUTTON_POS = {SCREEN_X / 2.0f + 190, SCREEN_Y / 2.0f + 153};
        //endingPage
        const sf::Vector2f REPLAY_BUTTON_POS = {SCREEN_X/2.0f-85, SCREEN_Y/2.0f+70};
        const sf::Vector2f TO_MENU_BUTTON_POS = {SCREEN_X/2.0f+85, SCREEN_Y/2.0f+70};

    const int PRINT_IMMORTAL = -1;
};