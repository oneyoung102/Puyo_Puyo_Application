#include <vector>
#include <utility>

namespace puyoImageConstant//화면을 구성하는 이미지 크기와 관련한 클래스
{
    //puyo_board.png
        //gamePage
        const unsigned int SCREEN_X = 640, SCREEN_Y = 444;
        const std::vector<std::pair<int,int>> PLAYER_BOARD_POS = {std::make_pair(31,35),std::make_pair(386+31,35)};
        const int BOARD_HEIGHT = 12;

        const std::vector<std::pair<int,int>> PLAYER_NEXT_PUYO_VIEWER_POS = {std::make_pair(244,62),std::make_pair(367,62)};
        const int NEXT_PUYO_VIEWER_BREADTH = 36;

        const int SCREEN_BAR_FROM_X = 302, SCREEN_BAR_FROM_Y = 60, SCREEN_BAR_TO_X = 38, SCREEN_BAR_TO_Y = 100;

        const std::vector<std::pair<int,int>> PLAYER_OBSTRUCT_VIEWER_POS = {std::make_pair(31,2),std::make_pair(386+31,2)};

    //puyos.png
        //gamePage
        const int PUYO_SIZE = 32;

        const double FUTURE_PUYO_ALPHA_VALUE = 0.7;

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
        const std::vector<std::pair<int,int>> PLAYER_SCORE_POS = {std::make_pair(246,204),std::make_pair(255,256)};

    //Text
        //gamePage
        const std::vector<std::pair<int,int>> TEXT_PLAYER_CHAIN_POS = {std::make_pair(126,205),std::make_pair(386+126,205)};
        const std::vector<std::pair<int,int>> TEXT_PLAYER_ALL_CLEAR_POS = {std::make_pair(126,241),std::make_pair(386+126,241)};
            //speed up mode
            const int TEXT_SPEED_UP_X = SCREEN_X/2, TEXT_SPEED_UP_Y = 310;
        //openingPage
        const int TEXT_PRESS_ENTER_X = SCREEN_X/2, TEXT_PRESS_ENTER_Y = SCREEN_Y/2+20;
        //menuPage
        const int TEXT_ARCADE_X = SCREEN_X/2, TEXT_ARCADE_Y = SCREEN_Y/2-120;
        //endingPage
        const int TEXT_WINNER_X = SCREEN_X/2, TEXT_WINNER_Y = SCREEN_Y/2-35;
    
    //button
        const int TEXT_SIZE_IN_BUTTON = 31;//5글자 기준 기본 텍스트 사이즈
        //menuPage
        const int SOLO_BUTTON_X = SCREEN_X/2-170, SOLO_BUTTON_Y = SCREEN_Y/2+23;
        const int DUAL_BUTTON_X = SCREEN_X/2, DUAL_BUTTON_Y = SCREEN_Y/2+23;
        const int BOT_BUTTON_X = SCREEN_X/2+170, BOT_BUTTON_Y = SCREEN_Y/2+23;
        //openingPage
        //optionPage
        const int DIFF_DIAL_BUTTON_X = SCREEN_X / 2-130, DIFF_DIAL_BUTTON_Y = SCREEN_Y/2-5;
        const int MODE_DIAL_BUTTON_X = SCREEN_X / 2+130, MODE_DIAL_BUTTON_Y = SCREEN_Y/2-5;

        const int BACK_BUTTON_X = SCREEN_X / 2 - 190, BACK_BUTTON_Y = SCREEN_Y / 2 + 153;
        const int READY_BUTTON_X = SCREEN_X / 2 + 190, READY_BUTTON_Y = SCREEN_Y / 2 + 153;
        //endingPage
            const int REPLAY_BUTTON_X = SCREEN_X/2-85, REPLAY_BUTTON_Y = SCREEN_Y/2+70;
            const int TO_MENU_BUTTON_X = SCREEN_X/2+85, TO_MENU_BUTTON_Y = SCREEN_Y/2+70;

    const int PRINT_IMMORTAL = -1;
};