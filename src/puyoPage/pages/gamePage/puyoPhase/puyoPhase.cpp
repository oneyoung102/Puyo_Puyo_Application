#include "puyoPage/pages/gamePage/puyoPhase/puyoPhase.hpp"
#include "puyoPage/pages/gamePage/puyoPhase/puyoMode/puyoModeBomb.hpp"
#include "puyoPage/pages/gamePage/puyoPhase/puyoMode/puyoModeSpeed.hpp"
#include "puyoPage/pages/gamePage/puyoTempPuyo/puyoGravityPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoTempPuyo/puyoVanishPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoTempPuyo/puyoAction/puyoPuyoGravity_temp.hpp"
#include "puyoPage/pages/gamePage/puyoTempPuyo/puyoAction/puyoPuyoVanish_temp.hpp"
#include "puyoPage/puyoPageManager/puyoPageSignal.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"

#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoPhase/puyoScoreCalc.hpp"

#include "puyoPage/pages/gamePage/puyoPhase/puyoMode/puyoModeBasic.hpp"

#include <vector>
#include <algorithm>
#include <memory>

using namespace std;
using namespace puyoImageConstant;
using namespace puyoGameConstant;

puyoPhase::puyoPhase()
    : gen(random_device{}())
{
    game_end = false;
    color_count = 0;
    win_player_num = NO_WINNER;
    calc = puyoScoreCalc();
}

puyoPhase::Phase puyoPhase::get_phase(puyoBoard& board)
{
    if(!board.controll_vanish().vanish_puyo_empty())
        return puyoPhase::Phase::vanish;
    if(!board.controll_gravity().gravity_puyo_empty())
        return puyoPhase::Phase::gravity;
    return puyoPhase::Phase::play;
}

void puyoPhase::delay(int player_num, int time){delay_times[player_num] += time;}
void puyoPhase::wait(int player_num){delay_times[player_num] = max(delay_times[player_num]-1,0);}
bool puyoPhase::is_delayed(int player_num){return delay_times[player_num] > 0;}

pair<puyoType,puyoType> puyoPhase::get_new_puyo_color(int count)
{
    while(new_colors.size() < count+3)//다음에 나올 뿌요를 보여주기 위해 +3
    {
        uniform_int_distribution<> dist1(0, color_count-1);
        uniform_int_distribution<> dist2(0, color_count-1);
        new_colors.push_back(make_pair((puyoType)dist1(gen),(puyoType)dist2(gen)));
    }
    return new_colors[count];
}
const vector<pair<puyoType,puyoType>>& puyoPhase::get_new_colors(){return new_colors;}

bool puyoPhase::game_ended(){return game_end;}
void puyoPhase::end_game(){game_end = true;}

void puyoPhase::set_game(Diff diff, Mode mode)
{
//////난이도
    switch(diff)
    { 
        case Diff::easy :
            tie(gravity_value,stay_value,color_count) = EASY_DIFF_SETTING;
            break;
        case Diff::normal :
            tie(gravity_value,stay_value,color_count) = NORMAL_DIFF_SETTING;
            break;
        case Diff::hard :
            tie(gravity_value,stay_value,color_count) = HARD_DIFF_SETTING;
            break;
        case Diff::NONE :
            break;
    } 
//////플레이어 기본 설정
    for(const auto& player : players)
    {
        player->get_board().set_puyo_spawn_pos(PLAYPUYO_IN_BOARD_SPAWN_X,PLAYPUYO_IN_BOARD_SPAWN_Y);
        player->get_board().controll_vanish().set_condition_for_vanish(PUYO_VANISH_CONDITION);
        player->give_new_puyo(get_new_puyo_color(player->get_new_puyo_count()),gravity_value,stay_value);
    }
//////모드
    mode_type = mode;
    switch(mode_type)
    {
        case Mode::basic :
            curr_mode = make_unique<puyoModeBasic>();
            break;
        case Mode::speed :
            curr_mode = make_unique<puyoModeSpeed>(gravity_value);
            break;
        case Mode::bomb :
            curr_mode = make_unique<puyoModeBomb>(get_player_count());
            break;
        case Mode::NONE : 
            throw runtime_error("curr mode ptr is nullptr");
            break;
    }
    delay_times = vector<int>(players.size(),0);
}

void puyoPhase::proceed_game()
{
    for(const auto& player : players)
    {
        auto& board = player->get_board();
        auto& cv = board.controll_vanish();
        auto& cs = board.controll_score();
        auto& cg = board.controll_gravity();
        auto& cf = board.controll_future();
        auto& ce = board.controll_energy();
        auto& co = board.controll_obstuct();

        auto& puyo = player->get_puyo();
        const int player_num = player->get_player_num();
        const int opposite = player_num^1;
      
        wait(player_num);
        ce.fly_energy_puyos(board);
/////////////////봇이라면 행동
        if(player->is_bot())
            if(get_phase(board) == Phase::play && !is_delayed(player_num))
                player->act_bot_let(); 
/////////////////모드 진행
        curr_mode->proceed_mode(*this, *player);

        int added_score = 0;
        bool change_to_play_phase = false;
        switch(get_phase(board))
        {
            case Phase::play :
                if(is_delayed(player_num))
                    break;
                cf.find_future_puyos(board,puyo);
                puyo.gravity_let(board);
                puyo.act_let(board);

                if(puyo.is_down())
                    ++added_score;
                else if(puyo.is_dropped())
                {
                    added_score += puyo.get_drop_height(board);
                    cf.remove_future_puyos();
                    cg.push_gravity_puyo(puyo.to_gravity_puyo());
                    player->give_new_puyo(this->get_new_puyo_color(player->get_new_puyo_count()),gravity_value,stay_value);
                    player->sign_puyo_dropped();
                    co.approve_spawn_obstruct_puyo();
                }
                break;

            case Phase::gravity :
                cg.gravity_gravity_puyos(board);
                if(cg.gravity_puyo_empty())
                {             
                    cv.find_vanish_puyo(board); 
                    if(cv.vanish_puyo_empty()) //파괴할 뿌요가 없으면
                    {
                        change_to_play_phase = true;
                        co.spawn_obstruct_puyo(board,calc.get_obstruct_puyo_for_dropping(co.get_obstruct_puyo()));
                    }
                    else
                    {
                        cs.add_chain_count(board);
                        const int add_score = calc.get_add_score(cs.get_puyo_count(),cs.get_chain_count(),cs.get_link_count(),cs.get_color_count());
                        added_score += add_score;
                    }
                }
                break;

            case Phase::vanish :
                cv.vanish_vanish_puyos(board);
                if(cv.vanish_puyo_empty())
                {
                    cg.find_gravity_puyo(board); 
                    if(cg.gravity_puyo_empty()) //파괴 후, 드롭할 뿌요가 없으면
                    {
                        change_to_play_phase = true;
                        if(board.is_all_cleared())
                            player->add_opposite_obstruct_puyo_count(calc.get_all_cleared_obstruct_puyo());//올클리어 보너스
                    }
                }
                break;
        };
        if(change_to_play_phase)
        {
            delay(player_num,1500);
            cs.reset_chain_count();
            co.disapprove_spawn_obstruct_puyo();
        }
//////////점수 관련 연산
        player->add_score(added_score);
        if(players.size() != 1)
        {
            player->add_opposite_obstruct_puyo_count(calc.score_to_obstruct_puyo(added_score));
            if(player->get_opposite_obstruct_puyo_count() > 0) 
            {
                if(!ce.temp_energy_puyo_empty())
                {
                    const auto[self,opp] = calc.get_obstruct_puyo_count(player->get_opposite_obstruct_puyo_count(),co.get_obstruct_puyo());
                    co.give_obstruct_puyo(-self);

                    players[opposite]
                    ->get_board()
                    .controll_obstuct()
                    .give_obstruct_puyo(opp);
                    player->clear_opposite_obstruct_puyo_count();

                    const auto[bx,by] = PLAYER_BOARD_POS[player_num];//에너지 뿌요 생성
                    const auto[ox,oy] = PLAYER_OBSTRUCT_VIEWER_POS[opposite];//에너지 뿌요 생성
                    ce.find_energy_puyos(bx,by,ox,oy);//에너지 뿌요 생성
                }
            } 
            else
                ce.clear_temp_energy_puyos();
        }
/////////게임 종료
        if(cg.gravity_puyo_is_out() && cg.gravity_puyo_empty())//게임 종료
        {
            win_player_num = opposite;
            end_game(); 
        }        
    }

}
int puyoPhase::get_player_count(){return (int)players.size();}
const vector<unique_ptr<puyoPlayer>>& puyoPhase::get_players(){return players;}
void puyoPhase::add_player(unique_ptr<puyoPlayer>&& player)
{
    if(players.size() == 2)
        throw runtime_error("Player count must be 1 or 2");
    players.push_back(std::move(player));
}
int puyoPhase::get_gravity_value(){return gravity_value;}
void puyoPhase::set_gravity_value(int value){gravity_value = value;}
int puyoPhase::get_stay_value(){return stay_value;}
void puyoPhase::set_stay_value(int value){stay_value = value;}
int puyoPhase::get_color_count(){return color_count;}
void puyoPhase::set_color_count(int value){color_count = value;}
Mode puyoPhase::get_mode_type(){return mode_type;}

int puyoPhase::get_win_player_num()
{
    if(players.size() == 1)
        return NO_WINNER;//이긴 사람 없음 == 솔로 플레이
    return win_player_num;
}
void puyoPhase::set_win_player_num(int num){win_player_num = num;}