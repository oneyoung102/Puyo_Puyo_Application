#pragma once

#include "puyoBoard.hpp"
#include "puyoPuyo.hpp"

#include <vector>

using namespace std;

class puyoPlayer
{
    private :
        puyoBoard board;
        puyoPuyo puyo;

        int player_num; // 0 또는 1
        char left_key, right_key;

    public :

        puyoPlayer(int pn, puyoBoard&& b/*,char lk, char rk ...*/);


        int get_player_num();
        puyoBoard& get_board();
        puyoPuyo& get_puyo();

        void give_puyo(puyoPuyo&& p);
};