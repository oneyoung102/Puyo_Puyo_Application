#pragma once

#include "puyoBoard.hpp"
#include "puyoPlayPuyo.hpp"
#include "puyoPhase/puyoPhasing.hpp"

#include <vector>

using namespace std;

class puyoPlayer
{
    private :
        puyoBoard board;
        puyoPlayPuyo puyo;
        puyoPhasing phase;

        int player_num; // 0 또는 1
        char left_key, right_key;

    public :

        puyoPlayer(int pn, puyoBoard&& b, puyoPhasing&& p);


        int get_player_num();
        puyoBoard& get_board();
        puyoPlayPuyo& get_puyo();
        puyoPhasing& get_phase();

        void give_puyo(puyoPlayPuyo&& p);
};