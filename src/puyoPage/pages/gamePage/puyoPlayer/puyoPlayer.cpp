#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoPage/puyoLet.hpp"
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
        throw runtime_error("Player number is neither 0 nor 1");

    score = 0;
    new_puyo_count = 0;

    if(player_is_bot)
        bot_algorithm = std::move(make_unique<puyoBotAlgorithm>());
    else
        bot_algorithm = nullptr;
}

int puyoPlayer::get_player_num() const {return player_num;}
puyoBoard& puyoPlayer::get_board() const {return *board;}
puyoPlayPuyo& puyoPlayer::get_puyo() const {return *puyo;}

const int& puyoPlayer::get_score() const {return score;}
void puyoPlayer::add_score(int s){score += s;}

void puyoPlayer::give_new_puyos(pair<puyoType,puyoType> types, int puyo_gravity_value, int puyo_stay_value)
{
    puyo = std::move(make_unique<puyoPlayPuyo>(board->get_spawn_pos(),types,puyo_gravity_value,puyo_stay_value));
    ++new_puyo_count;
}
const int& puyoPlayer::get_new_puyo_count() const {return new_puyo_count;}

function<void()> puyoPlayer::get_let_left(){return FUNCFY(get_puyo().let_left);}
function<void()> puyoPlayer::get_let_right(){return FUNCFY(get_puyo().let_right);}
function<void()> puyoPlayer::get_let_down(){return FUNCFY(get_puyo().let_down);}
function<void()> puyoPlayer::get_let_turn(){return FUNCFY(get_puyo().let_turn);}
function<void()> puyoPlayer::get_let_drop(){return FUNCFY(get_puyo().let_drop);}

void puyoPlayer::signal_puyo_drop(){set_signal(puyoPlayerSignal::puyo_dropped);}

bool puyoPlayer::is_bot() const {return player_is_bot;}
void puyoPlayer::act_bot_let() const
{
    if(bot_algorithm->bot_lets_empty())
        bot_algorithm->think_perfect_lets(*board, *puyo);
    else if(!puyo->moving())
        bot_algorithm->let_bot_act();
}