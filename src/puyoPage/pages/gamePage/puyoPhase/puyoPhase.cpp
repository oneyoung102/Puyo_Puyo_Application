#include "puyoPage/pages/gamePage/puyoPhase/puyoPhase.hpp"
#include "puyoPage/pages/gamePage/puyoPhase/puyoMode/puyoModeBomb.hpp"
#include "puyoPage/pages/gamePage/puyoPhase/puyoMode/puyoModeSpeed.hpp"

#include "puyoPage/pages/gamePage/puyoPhase/puyoPhaseStatement.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoAction/puyoPuyoGravity.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoAction/puyoPuyoVanish.hpp"

#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/puyoType.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/types/_puyoType.hpp"

#include "puyoPage/puyoPageManager/puyoPageSignal.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"

#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoPhase/puyoScoreCalc.hpp"

#include "puyoPage/pages/gamePage/puyoPhase/puyoMode/puyoModeBasic.hpp"

#include <vector>
#include <memory>

using namespace std;
using namespace puyoGameConstant;

puyoPhase::puyoPhase()
    : gen(random_device{}())
    , game_end(false)
    , win_player_num(NO_WINNER)
{}

pair<puyoType,puyoType> puyoPhase::get_new_puyos (int count)
{
    while(new_types.size() < count+1+NEXT_PUYO_COUNT_DISPLAY) //다음에 나올 뿌요를 보여주기 위해 NEXT_PUYO_COUNT_DISPLAY개수 더 더하기
    {
        uniform_int_distribution<> dist1(0, color_count-1);
        uniform_int_distribution<> dist2(0, color_count-1);
        new_types.push_back({
            puyoType(make_unique<puyoColor>((_puyoType::Type)dist1(gen))),
            puyoType(make_unique<puyoColor>((_puyoType::Type)dist2(gen)))});
    }
    return new_types[count];
}
const vector<pair<puyoType,puyoType>>& puyoPhase::get_new_types() const {return new_types;}

bool puyoPhase::game_ended() const {return game_end;}
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
        player->get_board().set_spawn_pos(PLAYPUYO_IN_BOARD_SPAWN_POS);
        player->get_board().controll_vanish().set_condition(PUYO_VANISH_CONDITION);
        player->give_new_puyos(get_new_puyos(player->get_new_puyo_count()),gravity_value,stay_value);
        player->get_board().controll_future().update(player->get_board(),player->get_puyo());
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
    pstate = puyoPhaseStatement(players.size());
}

////////////////////////////////////////////////////////////////////////////////////////////

void puyoPhase::proceed_play(const unique_ptr<puyoPlayer>& player, int& added_score)
{
    auto& board = player->get_board();
    auto& cf = board.controll_future();
    auto& puyo = player->get_puyo();
    const int player_num = player->get_player_num();

    cf.fall(board);
    puyo.gravity_let(board);
    puyo.act_let(board);

    if(puyo.down())
        ++added_score;
    else if(puyo.dropped(board))
    {
        added_score += puyo.get_height(board);
        auto& cs = board.controll_score();
        auto& co = board.controll_obstuct();
        auto& cg = board.controll_gravity();
        cs.reset_chain_count();
        cg.add(puyo.to_gravity_puyo(board));
        player->give_new_puyos(this->get_new_puyos(player->get_new_puyo_count()),gravity_value,stay_value);
        cf.update(board,player->get_puyo());
        player->signal_puyo_drop();
        co.approve_spawn();
        pstate.set_phase(player_num,puyoPhaseStatement::Phase::gravity);
    }
}
void puyoPhase::proceed_gravity(const unique_ptr<puyoPlayer>& player, int& added_score)
{
    auto& board = player->get_board();
    auto& cg = board.controll_gravity();
    const int player_num = player->get_player_num();

    cg.gravity(board);
    if(cg.empty())
    {             
        auto& cv = board.controll_vanish();
        auto& cs = board.controll_score();
        const auto [puyo_count, link_count, color_count] = cv.to_vanish_puyo(board); 
        cs.add_puyo_count(puyo_count);
        cs.add_link_count(link_count);
        cs.add_color_count(color_count);
        if(cv.empty()) //파괴할 뿌요가 없으면
        {
            auto& co = board.controll_obstuct();
            if(co.spawn_approved())
            {
                cg.add(co.to_gravity_puyo(board,calc.get_obstruct_puyo_for_dropping(co.get())));
                co.disapprove_spawn();
            }
            else
            {
                pstate.set_phase(player_num,puyoPhaseStatement::Phase::play);
                pstate.delay(player_num,PHASE_SET_TICK);
            }
        }
        else
        {
            auto& cs = board.controll_score();
            cs.add_chain_count(board);
            added_score += calc.get_add_score(cs.get_puyo_count(),cs.get_chain_count(),cs.get_link_count(),cs.get_color_count());
            pstate.set_phase(player_num,puyoPhaseStatement::Phase::vanish);
        }
    }
}
void puyoPhase::proceed_vanish(const unique_ptr<puyoPlayer>& player, int& added_score)
{
    auto& board = player->get_board();
    auto& cv = board.controll_vanish();
    const int player_num = player->get_player_num();

    cv.vanish(board);
    if(cv.empty())
    { 
        auto& cg = board.controll_gravity();
        auto& co = board.controll_obstuct();
        cg.add(board.to_gravity_puyo()); 
        if(cg.empty()) //파괴 후, 드롭할 뿌요가 없으면
        {
            auto& cs = board.controll_score();
            cs.reset_chain_count();
            if(board.all_cleared())
                added_score += calc.get_all_cleared_score();//올클리어 보너스
            pstate.set_phase(player_num,puyoPhaseStatement::Phase::play);
            pstate.delay(player_num,PHASE_SET_TICK);
        }
        else
            pstate.set_phase(player_num,puyoPhaseStatement::Phase::gravity);
    }
}

void puyoPhase::calc_obstruct(const std::unique_ptr<puyoPlayer>& player, int& added_score)
{
    if(players.size() == 1)
        throw runtime_error("Obstruct puyo spawn is prohibited in Solo");

    auto& board = player->get_board();
    auto& ce = board.controll_energy();
    auto& co = board.controll_obstuct();
    
    co.add_opp(calc.to_obstruct_puyo(added_score));
    if(!co.empty_opp()) 
    {
        auto& cv = board.controll_vanish();
        if(cv.empty())
        {
            const int player_num = player->get_player_num(), opposite = player_num^1;
            const int opp = calc.get_opposite_obstruct_puyo_count(co.get(),co.get_opp());

            const int to_player_num = (co.get() > 0) ? player_num : opposite;
            ce.to_energy_puyo(player_num,to_player_num);//에너지 뿌요 생성

            co.add(-co.get_opp());
            co.clear_opp();
            players[opposite]->get_board().controll_obstuct().add(opp);
        }
    } 
    else
        ce.clear_temp(); 
}

void puyoPhase::proceed_game()
{
    for(const auto& player : players)
    {
        auto& board = player->get_board();
        const int player_num = player->get_player_num();
/////////////////봇이라면 행동
        if(player->is_bot())
            if(pstate.is_phase(player_num,puyoPhaseStatement::Phase::play) && !pstate.delayed(player_num))
                player->act_bot_let(); 
/////////////////모드 진행
        curr_mode->proceed_mode(*this, *player);

        board.controll_energy().fly(board);
        int added_score = 0;
        switch(pstate.get_phase(player_num))
        {
            case puyoPhaseStatement::Phase::play :
                pstate.wait(player_num);
                if(pstate.delayed(player_num))
                    break;
                proceed_play(player,added_score);
                break;
            case puyoPhaseStatement::Phase::gravity :
                proceed_gravity(player,added_score);
                break;

            case puyoPhaseStatement::Phase::vanish :
                proceed_vanish(player,added_score);
                break;
        };
        player->add_score(added_score);
        if(get_player_count() == 2)
            calc_obstruct(player,added_score);
        else
            board.controll_energy().clear_temp(); 
/////////게임 종료
        if(board.controll_gravity().out() && board.controll_gravity().empty())//게임 종료
        {
            const int opposite = player_num^1;
            win_player_num = opposite;
            end_game(); 
            break;
        }        
    }
}

////////////////////////////////////////////////////////////////////////////////////////////

int puyoPhase::get_player_count() const {return players.size();}
const vector<unique_ptr<puyoPlayer>>& puyoPhase::get_players() const {return players;}
void puyoPhase::add_player(unique_ptr<puyoPlayer>&& player)
{
    if(players.size() == 2)
        throw runtime_error("Player count must be 1 or 2");
    players.push_back(std::move(player));
}
int puyoPhase::get_gravity_value() const {return gravity_value;}
void puyoPhase::set_gravity_value(int value){gravity_value = value;}
int puyoPhase::get_stay_value() const {return stay_value;}
void puyoPhase::set_stay_value(int value){stay_value = value;}
int puyoPhase::get_color_count() const {return color_count;}
void puyoPhase::set_color_count(int value){color_count = value;}
Mode puyoPhase::get_mode_type() const {return mode_type;}

int puyoPhase::get_win_player_num() const
{
    if(players.size() == 1)
        return NO_WINNER;//이긴 사람 없음 == 솔로 플레이
    return win_player_num;
}
void puyoPhase::set_win_player_num(int num){win_player_num = num;}

puyoPhaseStatement& puyoPhase::get_pstate(){return pstate;}