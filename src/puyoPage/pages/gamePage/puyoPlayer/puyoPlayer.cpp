#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoPlayer/puyoPlayer.hpp"
#include "puyoPage/pages/gamePage/puyoPlayer/puyoBot/puyoBotModel1.hpp"
#include "puyoPage/pages/gamePage/puyoPlayer/puyoBot/puyoBotModel2.hpp"
#include "puyoPage/pages/gamePage/puyoPlayer/puyoBot/puyoBotModel3.hpp"

#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"

#include <functional>

using namespace std;

puyoPlayer::puyoPlayer(int player_num, unique_ptr<puyoBoard>&& board, bool player_is_bot, int model, unsigned int init_act_tick, const std::vector<std::pair<puyoPuyo,puyoPuyo>>& new_types)
    : board(std::move(board))
    , puyoObjectSignal()
    , player_num(player_num)
    , player_is_bot(player_is_bot)
    , score(0)
    , new_puyo_count(0)
{
    if(player_num != 0 && player_num != 1)
        throw runtime_error("Player number is neither 0 nor 1");
    switch(model)
    {
        case 1 :
            bot_model = make_unique<puyoBotModel1>(this->board->get_size(), init_act_tick);
            break;
        case 2 :
            bot_model = make_unique<puyoBotModel2>(score,this->board->get_size(), init_act_tick);
            break;
        case 3 :
            bot_model = make_unique<puyoBotModel3>(new_types,new_puyo_count, this->board->get_size(), init_act_tick);
            break;
        default :
            throw runtime_error("Model number is not 1, 2, or 3");
    }
}

int puyoPlayer::get_player_num() const {return player_num;}
int puyoPlayer::get_opposite() const {return player_num^1;};
puyoBoard& puyoPlayer::get_board() const {return *board;}
puyoPlayPuyo& puyoPlayer::get_puyo() const {return *puyo;}

const int& puyoPlayer::get_score() const {return score;}
void puyoPlayer::add_score(int s){score = min(puyoGameConstant::SCORE_UPPER-1,score+s);}

void puyoPlayer::give_new_puyos(const pair<puyoPuyo,puyoPuyo>& puyos, int puyo_gravity_value, int puyo_stay_value)
{
    auto temp_puyos = puyos;
    temp_puyos.first.move(board->get_spawn_pos());
    temp_puyos.second.move(board->get_spawn_pos()-POSi(0,1));
    puyo = make_unique<puyoPlayPuyo>(std::move(temp_puyos),puyo_gravity_value,puyo_stay_value);
    ++new_puyo_count;
}
const int& puyoPlayer::get_new_puyo_count() const {return new_puyo_count;}

function<void()> puyoPlayer::get_let_left(){return [this](){ if(puyo) get_puyo().let_left(); };}
function<void()> puyoPlayer::get_let_right(){return [this](){ if(puyo) get_puyo().let_right(); };}
function<void()> puyoPlayer::get_let_down(){return [this](){ if(puyo) get_puyo().let_down(); };}
function<void()> puyoPlayer::get_let_turn(){return [this](){ if(puyo) get_puyo().let_turn(); };}
function<void()> puyoPlayer::get_let_drop(){return [this](){ if(puyo) get_puyo().let_drop(); };}

bool puyoPlayer::is_bot() const {return player_is_bot;}
void puyoPlayer::act_bot_let() const
{
    if(bot_model->bot_lets_empty())
        bot_model->think_perfect_lets(*this);
    else if(!puyo->moving())
        bot_model->let_bot_act();
}

puyoBoardEnergyControll& puyoPlayer::controll_energy(){return energy_controll;}
puyoBoardGravityControll& puyoPlayer::controll_gravity(){return gravity_controll;}
puyoBoardScoreControll& puyoPlayer::controll_score(){return score_controll;}
puyoBoardObstructControll& puyoPlayer::controll_obstuct(){return obstuct_controll;}
puyoBoardVanishControll& puyoPlayer::controll_vanish(){return vanish_controll;}
puyoBoardFutureControll& puyoPlayer::controll_future(){return future_controll;}
const puyoBoardEnergyControll& puyoPlayer::controll_energy() const {return energy_controll;}
const puyoBoardGravityControll& puyoPlayer::controll_gravity() const {return gravity_controll;}
const puyoBoardScoreControll& puyoPlayer::controll_score() const {return score_controll;}
const puyoBoardObstructControll& puyoPlayer::controll_obstuct() const {return obstuct_controll;}
const puyoBoardVanishControll& puyoPlayer::controll_vanish() const {return vanish_controll;}
const puyoBoardFutureControll& puyoPlayer::controll_future() const {return future_controll;}

void puyoPlayer::act_play_puyo()
{
    future_controll.fall(*board);
    puyo->gravity_let(*board);
    puyo->act_let(*board);
}
int puyoPlayer::do_after_puyo_dropped(pair<puyoPuyo,puyoPuyo>&& new_puyos, int gravity_value, int stay_value)
{
    const int added_score =  score_controll.get_drop_score(future_controll.get(),*puyo);

    gravity_controll.add(puyo->to_gravity_puyo(*board));
    give_new_puyos(new_puyos,gravity_value,stay_value);
    
    future_controll.spawn(*board,*puyo);
    obstuct_controll.approve_spawn();

    set_signal(puyoPlayerSignal::puyo_dropped);//모든 proceed 메서드 내부 구현들을 플레이어 쪽으로 옮긴 후에 시그널 추가

    return added_score;
}
bool puyoPlayer::act_gravity_puyos()
{
    gravity_controll.gravity(*board);
    return gravity_controll.empty();
}
bool puyoPlayer::test_and_prepare_vanish()
{
    auto [puyo_count, link_count, color_count, temp_energy_puyos] = vanish_controll.to_vanish_puyo(*board); 
    auto& cs = score_controll;
    cs.add_puyo_count(puyo_count);
    cs.add_link_count(std::move(link_count));
    cs.add_color_count(std::move(color_count));
    energy_controll.add(std::move(temp_energy_puyos));
    
    return vanish_controll.empty();
}
bool puyoPlayer::act_vanish_puyos()
{
    vanish_controll.vanish(*board);
    return vanish_controll.empty();
}
bool puyoPlayer::test_and_prepare_gravity()
{
    gravity_controll.add(board->to_gravity_puyo());
    return gravity_controll.empty();
}
bool puyoPlayer::test_spawn_obstruct_puyo(int obstruct_puyo_for_dropping)
{
    if(obstuct_controll.spawn_approved())
    {
        gravity_controll.add(obstuct_controll.to_gravity_puyo(*board,obstruct_puyo_for_dropping));
        obstuct_controll.disapprove_spawn();
        return true;
    }
    return false;
}