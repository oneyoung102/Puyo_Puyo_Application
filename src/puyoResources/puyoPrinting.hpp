#pragma once

#include <SFML/Graphics.hpp>

#include <tuple>

class puyoBoard;
class puyoPlayPuyo;


class puyoGravityPuyo;
class puyoVanishPuyo;
class puyoFuturePuyo;

using namespace std;
using namespace sf;

namespace puyoImageConstant//화면을 구성하는 이미지 크기와 관련한 클래스
{
    const unsigned int SCREEN_X = 638, SCREEN_Y = 444;
    const vector<pair<int,int>> PLAYER_BOARD_POS = {make_pair(31,35),make_pair(386+31,35)};

    const int PUYO_SIZE = 32;
    const int MAX_PUYO_COLOR = 5;

    const float FUTURE_PUYO_ALPHA_VALUE = 0.7;

    const int GRAVITY_PUYO_X = 4, GRAVITY_PUYO_Y = 13;
    const int VANISH_PUYO_X = 6, VANISH_PUYO_Y = 10;

    const int SPWAN_SPOT_CYCLE = 1000;
    const int SPWAN_SPOT_STATE_MAX = 5; 
    const int SPWAN_SPOT_STATE_X = 7, SPWAN_SPOT_STATE_Y = 12;  //이미지 위치 
};

using namespace puyoImageConstant;

class puyoPrinting
{
    private :
        RenderWindow& window;

        int spwan_spot_state;
        bool spawn_spot_rotate_dir;

        void print_sprite(Sprite sprite, float x, float y);

    public :
        puyoPrinting(RenderWindow& w);

        void print_spawn_spot(Sprite puyo, float x, float y, int player_num);
        
        void print_puyo(Sprite puyo, float x, float y, int color, int dir);

        void print_board(Sprite puyo, puyoBoard& board, int player_num);

        void print_player_puyo(Sprite puyo, puyoPlayPuyo& playPuyo, int player_num);
        void print_future_puyo(Sprite puyo, int player_num, vector<puyoFuturePuyo>&& future_puyos);
        void print_gravity_puyo(Sprite puyo, puyoBoard& board, int player_num, vector<puyoGravityPuyo>& temp_puyos);
        void print_vanish_puyo(Sprite puyo, puyoBoard& board, int player_num, vector<puyoVanishPuyo>& temp_puyos);

        void print_screen(Sprite screen, int player_count);
        void print_screen_head(Sprite screen);

};