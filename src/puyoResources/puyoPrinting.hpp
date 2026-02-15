#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "printObject/puyoPrintObject.hpp"

using namespace std;
using namespace sf;

namespace puyoImageConstant//화면을 구성하는 이미지 크기와 관련한 클래스
{
    //puyo_board.png
    const unsigned int SCREEN_X = 640, SCREEN_Y = 444;
    const vector<pair<int,int>> PLAYER_BOARD_POS = {make_pair(31,35),make_pair(386+31,35)};

    const vector<pair<int,int>> PLAYER_NEXT_PUYO_VIEWER_POS = {make_pair(244,62),make_pair(367,62)};
    const int NEXT_PUYO_BREADTH = 36;

    const int SCREEN_BAR_FROM_X = 302, SCREEN_BAR_FROM_Y = 60, SCREEN_BAR_TO_X = 38, SCREEN_BAR_TO_Y = 100;

    //puyo.png
    const int PUYO_SIZE = 32;
    const int MAX_PUYO_COLOR = 5;

    const float FUTURE_PUYO_ALPHA_VALUE = 0.7;

    const int GRAVITY_PUYO_X = 4, GRAVITY_PUYO_Y = 13;
    const int VANISH_PUYO_X = 6, VANISH_PUYO_Y = 10;

    const int SPAWN_SPOT_CYCLE = 1000;
    const int SPAWN_SPOT_STATE_MAX = 5; 
    const int SPAWN_SPOT_STATE_X = 7, SPAWN_SPOT_STATE_Y = 12;  //이미지 위치 

    //puyo_num.png
    const int NUM_SIZE_X = 18, NUM_SIZE_Y = 29;
    const vector<pair<int,int>> PLAYER_SCORE_POS = {make_pair(246,204),make_pair(255,256)};
};

using namespace puyoImageConstant;

class puyoPrinting
{
    private :
        RenderWindow& window;
        vector<unique_ptr<puyoPrintObject>> print_objects;
    public :
        puyoPrinting(RenderWindow& w);
        void print_all_objects();
        void add_print_object(unique_ptr<puyoPrintObject>&& object);

};