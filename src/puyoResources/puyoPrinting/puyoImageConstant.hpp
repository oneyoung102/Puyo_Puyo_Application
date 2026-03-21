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

        const float FUTURE_PUYO_ALPHA_VALUE = 0.7;

        const int DROPPING_PUYO_X = 4, DROPPING_PUYO_Y = 13;
        const int GRAVITY_PUYO_X = 5, GRAVITY_PUYO_Y = 11;
        const int VANISH_SOON_PUYO_X = 6, VANISH_SOON_PUYO_Y = 10, VANISH_STAY_PUYO_X = 0, VANISH_STAY_PUYO_Y = 12;

        const int SPAWN_SPOT_STATE_MAX = 5; 
        const int SPAWN_SPOT_STATE_X = 11, SPAWN_SPOT_STATE_Y = 12;  //이미지 위치 

        const int OBSTRUCT_PUYO_X = 10, OBSTRUCT_PUYO_Y = 12;//이미지 위치 
        const int OBSTRUCT_VANISH_PUYO_X = 10, OBSTRUCT_VANISH_PUYO_Y = 11;//이미지 위치 
        const int OBSTRUCT_PUYO_VIEWER_X = 6, OBSTRUCT_PUYO_VIEWER_Y = 15; //방해 뿌요 뷰어에 사용되는 이미지
        
        const int ENERGY_PUYO_X = 11, ENERGY_PUYO_Y = 11;//이미지 위치 

    //puyo_num.png
        //gamePage
        const int NUM_SIZE_X = 18, NUM_SIZE_Y = 29;
        const std::vector<std::pair<int,int>> PLAYER_SCORE_POS = {std::make_pair(246,204),std::make_pair(255,256)};

    //Text
        //gamePage
        const std::vector<std::pair<int,int>> PLAYER_CHAIN_POS = {std::make_pair(126,205),std::make_pair(386+126,205)};
        const std::vector<std::pair<int,int>> PLAYER_ALL_CLEAR_POS = {std::make_pair(126,241),std::make_pair(386+126,241)};
        //openingPage
        const int TEXT_PRESS_ENTER_X = SCREEN_X/2, TEXT_PRESS_ENTER_Y = SCREEN_Y/2+20;
        //endingPage
        const int TEXT_WINNER_X = SCREEN_X/2, TEXT_WINNER_Y = SCREEN_Y/2-35;
    
    //button
        const int TEXT_SIZE_IN_BUTTON = 31;//5글자 기준 기본 텍스트 사이즈
        //menuPage
        //openingPage
        //endingPage
            const int REPLAY_BUTTON_X = SCREEN_X/2-85, REPLAY_BUTTON_Y = SCREEN_Y/2+70;
            const int TO_MENU_BUTTON_X = SCREEN_X/2+85, TO_MENU_BUTTON_Y = SCREEN_Y/2+70;

    const int PRINT_IMMORTAL = -1;
};