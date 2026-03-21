#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoPlayer/puyoPlayer.hpp"

#include <cstddef>
#include <vector>
#include <functional>

using namespace std;

puyoPlayer::puyoPlayer(int pn, puyoBoard&& b, puyoPlayPuyo&& p, bool temp_player_is_bot)
    : board(std::move(b)),
    puyo(std::move(p)),//처음에는 쓰레기값
    puyoObjectSignal()
{
    score = 0;
    opposite_obstruct_puyo_count = 0;

    if(pn != 0 && pn != 1)
        throw runtime_error("Player number is not 0 or 1");
    player_num = pn;

    new_puyo_count = 0;

    player_is_bot = temp_player_is_bot;
    if(player_is_bot)
        bot_algorithm = std::move(make_unique<puyoBotAlgorithm>());
    else
        bot_algorithm = nullptr;
}

int puyoPlayer::get_player_num(){return player_num;}
puyoBoard& puyoPlayer::get_board(){return board;}
puyoPlayPuyo& puyoPlayer::get_puyo(){return puyo;}

const int& puyoPlayer::get_score(){return score;}
void puyoPlayer::add_score(int s){score += s;}
int puyoPlayer::get_opposite_obstruct_puyo_count(){return opposite_obstruct_puyo_count;}
void puyoPlayer::add_opposite_obstruct_puyo_count(int c){opposite_obstruct_puyo_count += c;}
void puyoPlayer::clear_opposite_obstruct_puyo_count(){opposite_obstruct_puyo_count = 0;}

void puyoPlayer::give_new_puyo(pair<int,int> colors, int puyo_gravity_value, int puyo_stay_value)
{
    puyo = std::move(puyoPlayPuyo(board.get_puyo_spawn_pos(),colors,puyo_gravity_value,puyo_stay_value));
    ++new_puyo_count;
}
const int& puyoPlayer::get_new_puyo_count(){return new_puyo_count;}

pair<float,float> puyoPlayer::get_puyo_spawn_pos(){return board.get_puyo_spawn_pos();}
void puyoPlayer::set_puyo_spawn_pos(float x, float y){board.set_puyo_spawn_pos(x,y);}
// int puyoPlayer::get_puyo_gravity_value(){return puyo_gravity_value;}
// void puyoPlayer::set_puyo_gravity_value(int v){puyo_gravity_value = v;}
// int puyoPlayer::get_puyo_stay_value(){return puyo_stay_value;}
// void puyoPlayer::set_puyo_stay_value(int v){puyo_stay_value = v;}
int puyoPlayer::get_condition_for_vanish(){return board.get_condition_for_vanish();}
void puyoPlayer::set_condition_for_vanish(int v){board.set_condition_for_vanish(v);}

function<void()> puyoPlayer::get_let_left(){return [this](){return get_puyo().let_left();};}
function<void()> puyoPlayer::get_let_right(){return [this](){return get_puyo().let_right();};}
function<void()> puyoPlayer::get_let_down(){return [this](){return get_puyo().let_down();};}
//function<void()> puyoPlayer::get_let_up(){return [this](){return get_puyo().let_up();};}
function<void()> puyoPlayer::get_let_turn(){return [this](){return get_puyo().let_turn();};}
function<void()> puyoPlayer::get_let_drop(){return [this](){return get_puyo().let_drop();};}

void puyoPlayer::sign_play_puyo_dropped(){signals[(int)puyoPlayerSignal::puyo_dropped] = true;}

bool puyoPlayer::is_bot(){return player_is_bot;}
void puyoPlayer::act_bot_let()
{
    if(bot_algorithm->bot_lets_empty())
        bot_algorithm->think_perfect_lets(board, puyo);
    else
        bot_algorithm->let_bot_act(puyo);
}