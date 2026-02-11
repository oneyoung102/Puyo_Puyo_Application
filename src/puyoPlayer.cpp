#include "puyoBoard.hpp"
#include "puyoPlayPuyo.hpp"
#include "puyoPlayer.hpp"

#include <vector>

using namespace std;

puyoPlayer::puyoPlayer(int pn, puyoBoard&& b, puyoPhasing&& p) : board(b), puyo(puyoPlayPuyo({0,0},{-1,-1})), phase(puyoPhasing())//처음에는 쓰레기값 
{
    if(pn != 0 && pn != 1)
        throw runtime_error("Player number is not 0 or 1");
    player_num = pn;
}

int puyoPlayer::get_player_num(){return player_num;}
puyoBoard& puyoPlayer::get_board(){return board;}
puyoPlayPuyo& puyoPlayer::get_puyo(){return puyo;}
puyoPhasing& puyoPlayer::get_phase(){return phase;}

void puyoPlayer::give_puyo(puyoPlayPuyo&& p){puyo = p;}