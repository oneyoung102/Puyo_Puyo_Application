#include "puyoPage/pages/gamePage/puyoPhase/puyoPhaseAsset/puyoPhaseControll.hpp"
#include <cmath>
#include <vector>

using namespace std;


puyoPhaseControll::puyoPhaseControll(size_t player_count)
    : curr_phases(player_count,Phase::play)
    , delay_times(player_count,0)
{}

puyoPhaseControll::Phase puyoPhaseControll::get_phase(int player_num) const {return curr_phases[player_num];}
void puyoPhaseControll::set_phase(int player_num, Phase phase){curr_phases[player_num] = phase;}
bool puyoPhaseControll::is_phase(int player_num, Phase phase) const {return curr_phases[player_num] == phase;}

void puyoPhaseControll::delay(int player_num, int time){delay_times[player_num] += time;}
void puyoPhaseControll::wait(int player_num){delay_times[player_num] = fmax(delay_times[player_num]-1,0);}
bool puyoPhaseControll::delayed(int player_num) const{return delay_times[player_num] > 0;}


void puyoPhaseControll::act_play_puyo(puyoPlayer& player)
{
    const auto& board = player.get_board();
    auto& puyo = player.get_puyo();

    player.controll_future().fall(board);
    puyo.gravity_let(board);
    puyo.act_let(board);
}
int puyoPhaseControll::do_after_puyo_dropped(puyoPlayer& player, PLAYPUYO&& new_puyos, int gravity_value, int stay_value)
{
    const auto& board = player.get_board();
    auto& cg = player.controll_gravity();
    auto& cf = player.controll_future();
    auto& co = player.controll_obstuct();

    const int added_score = player.controll_score().get_drop_score(cf.get(),player.get_puyo());

    cg.add(player.get_puyo().to_gravity_puyo(board));
    player.give_new_puyos(std::move(new_puyos),gravity_value,stay_value);
    
    cf.spawn(board,player.get_puyo());
    co.approve_spawn();

    player.signal(puyoPlayerSignal::puyo_dropped);

    return added_score;
}
bool puyoPhaseControll::act_gravity_puyos(puyoPlayer& player)
{
    auto& cg = player.controll_gravity();

    cg.gravity(player.get_board());
    return cg.empty();
}
bool puyoPhaseControll::test_and_prepare_vanish(puyoPlayer& player)
{
    auto& cv = player.controll_vanish();
    auto& cs = player.controll_score();

    auto [puyo_count, link_count, color_count, temp_energy_puyos] = cv.to_vanish_puyo(player.get_board()); 
    cs.add_puyo_count(puyo_count);
    cs.add_link_count(std::move(link_count));
    cs.add_color_count(std::move(color_count));
    player.controll_energy().add(std::move(temp_energy_puyos));
    
    return cv.empty();
}
bool puyoPhaseControll::act_vanish_puyos(puyoPlayer& player)
{
    auto& board = player.get_board();
    auto& cv = player.controll_vanish();

    cv.vanish(board);
    return cv.empty();
}
bool puyoPhaseControll::test_and_prepare_gravity(puyoPlayer& player)
{
    auto& cg = player.controll_gravity();

    cg.add(player.get_board().to_gravity_puyo());
    return cg.empty();
}
bool puyoPhaseControll::test_spawn_obstruct_puyo(puyoPlayer& player, int obstruct_puyo_for_dropping)
{
    auto& co = player.controll_obstuct();

    if(co.spawn_approved())
    {
        player.controll_gravity().add(co.to_gravity_puyo(player.get_board(),obstruct_puyo_for_dropping));
        co.disapprove_spawn();
        return true;
    }
    return false;
}
void puyoPhaseControll::reset_all_chain(puyoPlayer& player)
{
    if(is_phase(player.get_player_num(), puyoPhaseControll::Phase::play))
    {
        player.controll_obstuct().clear_accumulated_score();
        player.controll_score().reset_chain_count();
    }
}