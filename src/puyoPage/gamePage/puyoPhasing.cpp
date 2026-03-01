#include "puyoPhasing.hpp"
#include "puyoTempPuyo/puyoGravityPuyo.hpp"
#include "puyoTempPuyo/puyoVanishPuyo.hpp"
#include "puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoTempPuyo/puyoAction/puyoPuyoGravity_temp.hpp"
#include "puyoTempPuyo/puyoAction/puyoPuyoVanish_temp.hpp"
#include "../../puyoResources/puyoImageConstant.hpp"

#include "puyoBoard.hpp"
#include "puyoScoreCalc.hpp"

#include <vector>
#include <algorithm>
#include <memory>

using namespace std;
using namespace puyoImageConstant;

puyoPhasing::puyoPhasing()
    : gen(random_device{}())
{
    game_end = false;
    color_count = 0;
    win_player_num = -1;
    calc = puyoScoreCalc();
}

puyoPhasing::Phase puyoPhasing::get_phase(puyoBoard& board)
{
    if(!board.not_existed_vanish_puyo())
        return puyoPhasing::Phase::vanish;
    if(!board.not_existed_gravity_puyo())
        return puyoPhasing::Phase::gravity;
    return puyoPhasing::Phase::play;
}

void puyoPhasing::delay(int player_num, int time){delay_times[player_num] += time;}
void puyoPhasing::wait(int player_num){delay_times[player_num] = max(delay_times[player_num]-1,0);}
bool puyoPhasing::is_delayed(int player_num){return delay_times[player_num] > 0;}

pair<int,int> puyoPhasing::get_new_puyo_color(int count)
{
    while(new_colors.size() < count+3)//다음에 나올 뿌요를 보여주기 위해 +3
    {
        uniform_int_distribution<> dist1(0, color_count-1);
        uniform_int_distribution<> dist2(0, color_count-1);
        new_colors.push_back(make_pair(dist1(gen),dist2(gen)));
    }
    return new_colors[count];
}

vector<pair<int,int>>& puyoPhasing::get_new_colors(){return new_colors;}

bool puyoPhasing::game_ended(){return game_end;}
void puyoPhasing::end_game(){game_end = true;}
void puyoPhasing::set_game(float spawn_x, float spawn_y, int condition, int gravity, int stay, int cc)
{
    if(1 <= cc && cc <= MAX_PUYO_COLOR)
        color_count = cc;
    else
        throw runtime_error("Color Count is out of range");

    delay_times = vector<int>(players.size(),0);
    for(auto&& player : players)
    {
        player->set_puyo_spawn_pos(spawn_x,spawn_y);
        player->set_condition_for_vanish(condition);
        player->set_puyo_gravity_value(gravity);
        player->set_puyo_stay_value(stay);

        player->give_new_puyo(get_new_puyo_color(player->get_new_puyo_count()));
    }
}

void puyoPhasing::proceed_game()
{
    for(auto&& player : players)
    {
        auto& board = player->get_board();
        auto& puyo = player->get_puyo();
        const int player_num = player->get_player_num();
        
        wait(player_num);
        board.fly_energy_puyos();

        int added_score = 0;
        switch(get_phase(board))
        {
            case Phase::play :
                if(is_delayed(player_num))
                    break;
                if(player->is_bot())//봇이라면 행동
                    player->act_bot_let();

                board.find_future_puyos(puyo);
                puyo.gravity_let(board);
                puyo.act_let(board);
                if(puyo.is_down())
                    ++added_score;
                if(puyo.is_dropped())
                {
                    board.remove_future_puyos();
                    added_score += puyo.get_drop_height(board);
                    board.push_gravity_puyo(puyo.to_gravity_puyo());
                    player->give_new_puyo(get_new_puyo_color(player->get_new_puyo_count()));
                    player->sign_play_puyo_dropped();
                    board.reset_chain_count();
                    board.approve_spawn_obstruct_puyo();
                }
                break;

            case Phase::gravity :
                board.gravity_gravity_puyos();
                if(board.not_existed_gravity_puyo())
                {             
                    board.find_vanish_puyo(); 
                    if(board.not_existed_vanish_puyo()) //파괴할 뿌요가 없으면
                    {
                        delay(player_num,800);
                        board.spawn_obstruct_puyo(calc.get_obstruct_puyo_for_dropping(board.get_obstruct_puyo()));
                    }
                    else
                    {
                        board.add_chain_count();
                        const int add_score = calc.get_add_score(board.get_puyo_count(),board.get_chain_count(),board.get_link_count(),board.get_color_count());
                        added_score += add_score;
                    }
                }
                break;

            case Phase::vanish :
                board.vanish_vanish_puyos();
                if(board.not_existed_vanish_puyo())
                {
                    board.find_gravity_puyo(); 
                    if(board.not_existed_gravity_puyo()) //파괴 후, 드롭할 뿌요가 없으면
                    {
                        delay(player_num,1200);
                        if(board.is_all_cleared())
                            player->add_opposite_obstruct_puyo_count(calc.get_all_cleared_obstruct_puyo());//올클리어 보너스
                    }
                }
                break;
        };

        player->add_score(added_score);
        if(players.size() != 1) //방해 뿌요 연산
        {
            player->add_opposite_obstruct_puyo_count(calc.score_to_obstruct_puyo(added_score));
            if(player->get_opposite_obstruct_puyo_count() > 0) 
            {
                if(!board.not_existed_temp_energy_puyo())
                {
                    const int opposite = player_num^1;
                    const auto[self,opp] = calc.get_obstruct_puyo_count(player->get_opposite_obstruct_puyo_count(),board.get_obstruct_puyo());
                    board.give_obstruct_puyo(-self);
                    players[opposite]->get_board().give_obstruct_puyo(opp);
                    player->clear_opposite_obstruct_puyo_count();

                    const auto[bx,by] = PLAYER_BOARD_POS[player_num];
                    const auto[ox,oy] = PLAYER_OBSTRUCT_VIEWER_POS[opposite];
                    board.find_energy_puyos(bx,by,ox,oy);//에너지 뿌요 생성
                }
            } 
            else
                board.clear_temp_energy_puyos();
        }
        if(board.gravity_puyo_is_out() && board.not_existed_gravity_puyo())//게임 종료
        {
            win_player_num = player_num^1;
            end_game(); 
        }        
    }
}
int puyoPhasing::get_player_count(){return (int)players.size();}
vector<unique_ptr<puyoPlayer>>&& puyoPhasing::get_players(){return std::move(players);}
void puyoPhasing::add_player(unique_ptr<puyoPlayer>&& player)
{
    if(players.size() == 2)
        throw runtime_error("Player count must be 1 or 2");
    players.push_back(std::move(player));
}

int puyoPhasing::get_win_player_num()
{
    if(players.size() == 1)
        return -1;//이긴 사람 없음 == 솔로 플레이
    return win_player_num;
}