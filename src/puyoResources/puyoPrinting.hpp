#pragma once

#include <SFML/Graphics.hpp>

#include "../puyoPlayer.hpp"

#include <tuple>

using namespace std;
using namespace sf;

namespace puyoImageConstant//화면을 구성하는 이미지 크기와 관련한 클래스
{
    const unsigned int SCREEN_X = 638, SCREEN_Y = 444;
    const vector<pair<int,int>> PLAYER_BOARD_POS = {make_pair(31,35),make_pair(386+31,35)};
    const int PUYO_SIZE = 32;

};

using namespace puyoImageConstant;

class puyoPrinting
{
    private :
        RenderWindow& window;

        void printSprite(Sprite sprite, float x, float y);

    public :
        puyoPrinting(RenderWindow& w);
        
        void printPuyo(Sprite puyo, float x, float y, int color, int dir);

        void printBoard(Sprite puyo, puyoPlayer& player);

        void printPlayerPuyo(Sprite puyo, puyoPlayer& player);

        void printScreen(Sprite screen, int player_count);

};