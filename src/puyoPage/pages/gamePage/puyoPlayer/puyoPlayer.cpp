#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoPlayer/puyoPlayer.hpp"

#include <functional>

using namespace std;

puyoPlayer::puyoPlayer(int player_num, unique_ptr<puyoBoard>&& board, bool player_is_bot)
    : board(std::move(board))
    , puyoObjectSignal()
    , player_num(player_num)
    , player_is_bot(player_is_bot)
{
    if(player_num != 0 && player_num != 1)
        throw runtime_error("Player number is not 0 or 1");

    score = 0;
    new_puyo_count = 0;

    if(player_is_bot)
        bot_algorithm = std::move(make_unique<puyoBotAlgorithm>());
    else
        bot_algorithm = nullptr;
}

int puyoPlayer::get_player_num(){return player_num;}
puyoBoard& puyoPlayer::get_board(){return *board;}
puyoPlayPuyo& puyoPlayer::get_puyo(){return *puyo;}

const int& puyoPlayer::get_score(){return score;}
void puyoPlayer::add_score(int s){score += s;}

void puyoPlayer::give_new_puyos(pair<puyoType,puyoType> types, int puyo_gravity_value, int puyo_stay_value)
{
    puyo = std::move(make_unique<puyoPlayPuyo>(board->get_spawn_pos(),types,puyo_gravity_value,puyo_stay_value));
    ++new_puyo_count;
}
const int& puyoPlayer::get_new_puyo_count(){return new_puyo_count;}

function<void()> puyoPlayer::get_let_left(){return [this](){return get_puyo().let_left();};}
function<void()> puyoPlayer::get_let_right(){return [this](){return get_puyo().let_right();};}
function<void()> puyoPlayer::get_let_down(){return [this](){return get_puyo().let_down();};}
function<void()> puyoPlayer::get_let_turn(){return [this](){return get_puyo().let_turn();};}
function<void()> puyoPlayer::get_let_drop(){return [this](){return get_puyo().let_drop();};}

void puyoPlayer::sign_puyo_dropped(){set_signal(puyoPlayerSignal::puyo_dropped);}

bool puyoPlayer::is_bot(){return player_is_bot;}
void puyoPlayer::act_bot_let()
{
    if(bot_algorithm->bot_lets_empty())
        bot_algorithm->think_perfect_lets(*board, *puyo);
    else if(!puyo->moving())
        bot_algorithm->let_bot_act();
}