#include "puyoBoard.hpp"
#include "puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoPlayer.hpp"

#include <vector>
#include <functional>

using namespace std;

puyoPlayer::puyoPlayer(int pn, puyoBoard&& b, puyoPlayPuyo&& p)
    : board(std::move(b)),
    puyo(std::move(p))//처음에는 쓰레기값 
{
    if(pn != 0 && pn != 1)
        throw runtime_error("Player number is not 0 or 1");
    player_num = pn;
    new_puyo_count = 1;
    statement = Statement::play;
}

int puyoPlayer::get_player_num(){return player_num;}
puyoBoard& puyoPlayer::get_board(){return board;}
puyoPlayPuyo& puyoPlayer::get_puyo(){return puyo;}

void puyoPlayer::give_new_puyo(pair<int,int> colors)
{
    puyo = std::move(puyoPlayPuyo(get_board().get_puyo_spawn_pos(),colors,puyo_gravity_value));
    ++new_puyo_count;
}
int puyoPlayer::get_new_puyo_count(){return new_puyo_count;}

pair<float,float> puyoPlayer::get_puyo_spawn_pos(){return board.get_puyo_spawn_pos();}
void puyoPlayer::set_puyo_spawn_pos(float x, float y){board.set_puyo_spawn_pos(x,y);}
int puyoPlayer::get_puyo_gravity_value(){return puyo_gravity_value;}
void puyoPlayer::set_puyo_gravity_value(int v){puyo_gravity_value = v;};

function<void()> puyoPlayer::get_let_left(){return [this](){return get_puyo().let_left();};}
function<void()> puyoPlayer::get_let_right(){return [this](){return get_puyo().let_right();};}
function<void()> puyoPlayer::get_let_down(){return [this](){return get_puyo().let_down();};}
//function<void()> puyoPlayer::get_let_up(){return [this](){return get_puyo().let_up();};}
function<void()> puyoPlayer::get_let_turn(){return [this](){return get_puyo().let_turn();};}
function<void()> puyoPlayer::get_let_drop(){return [this](){return get_puyo().let_drop();};}

puyoPlayer::Statement puyoPlayer::get_statement(){return statement;}
void puyoPlayer::convert_statement(Statement s){statement = s;}