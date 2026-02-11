#include "puyoBoard.hpp"
#include "puyoPuyo.hpp"
#include "puyoPlayer.hpp"

#include <vector>

using namespace std;

puyoPlayer::puyoPlayer(int pn, puyoBoard&& b/*,char lk, char rk ...*/) : board(b), puyo(puyoPuyo(0,0,-1,-1))//처음에는 쓰레기값 
{
    if(pn != 0 && pn != 1)
        throw runtime_error("Player number is not 0 or 1");
    player_num = pn;
}

int puyoPlayer::get_player_num(){return player_num;}
puyoBoard& puyoPlayer::get_board(){return board;}
puyoPuyo& puyoPlayer::get_puyo(){return puyo;}

void puyoPlayer::give_puyo(puyoPuyo&& p){puyo = p;}