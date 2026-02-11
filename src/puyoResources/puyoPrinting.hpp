#pragma once

#include <SFML/Graphics.hpp>

#include <tuple>

class puyoTempPuyo;
class puyoBoard;
class puyoPlayPuyo;

struct future_puyo;

using namespace std;
using namespace sf;

namespace puyoImageConstant//화면을 구성하는 이미지 크기와 관련한 클래스
{
    const unsigned int SCREEN_X = 638, SCREEN_Y = 444;
    const vector<pair<int,int>> PLAYER_BOARD_POS = {make_pair(31,35),make_pair(386+31,35)};

    const int PUYO_SIZE = 32;
    const int MAX_PUYO_COLOR = 5;

    const float FUTURE_PUYO_ALPHA_VALUE = 0.7;
    const int TEMP_PUYO_X = 4, TEMP_PUYO_Y = 13;
};

using namespace puyoImageConstant;

class puyoPrinting
{
    private :
        RenderWindow& window;

        void print_sprite(Sprite sprite, float x, float y);

    public :
        puyoPrinting(RenderWindow& w);
        
        void print_puyo(Sprite puyo, float x, float y, int color, int dir);

        void print_board(Sprite puyo, puyoBoard& board, int player_num);

        void print_player_puyo(Sprite puyo, puyoPlayPuyo& playPuyo, int player_num);
        void print_future_puyo(Sprite puyo, int player_num, vector<future_puyo> future_puyos);
        void print_temp_puyo(Sprite puyo, puyoBoard& board, int player_num, vector<puyoTempPuyo>& temp_puyos);

        void print_screen(Sprite screen, int player_count);

};