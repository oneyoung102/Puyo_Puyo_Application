#include "puyoPage/pages/gamePage/puyoPhase/puyoPhase.hpp"
#include "puyoPage/pages/gamePage/puyoPhase/puyoMode/puyoModeBomb.hpp"
#include "puyoPage/pages/gamePage/puyoPhase/puyoMode/puyoModeFrozen.hpp"
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
#include "puyoTool/puyoCast.hpp"

#include <random>
#include <vector>
#include <memory>

using namespace std;
using namespace puyoGameConstant;

puyoPhase::puyoPhase()
    : gen(random_device{}())
    , game_end(false)
    , game_end_ask(false)
    , win_player_num(NO_WINNER)
{}

pair<puyoType,puyoType> puyoPhase::get_new_puyos (int count)
{
    if(new_type_list.empty())
        throw runtime_error("new type list is empty, so can't take new puyos");
    while(new_types.size() < count+1+DISPLAYED_NEXT_PUYO_COUNT) //다음에 나올 뿌요를 보여주기 위해 NEXT_PUYO_COUNT_DISPLAY개수 더 더하기
    {
        uniform_int_distribution<> dist1(0, new_type_list.size()-1);
        uniform_int_distribution<> dist2(0, new_type_list.size()-1);
        new_types.push_back({
            new_type_list[dist1(gen)],
            new_type_list[dist2(gen)]});
    }
    return new_types[count];
}
const vector<pair<puyoType,puyoType>>& puyoPhase::get_new_types() const {return new_types;}
vector<pair<puyoType,puyoType>>& puyoPhase::get_new_types() {return new_types;}

bool puyoPhase::game_ended() const {return game_end;}
bool puyoPhase::game_end_asked() const {return game_end_ask;}
void puyoPhase::end_game()
{
    if(game_end_ask)
        game_end = true;
}
void puyoPhase::ask_end_game() {game_end_ask = game_end_ask || true;}

void puyoPhase::set_game(Diff diff, Mode mode)
{
//////난이도
    int color_count = 0;
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
////// 색 뿌요 중에서 랜덤 선택
    const int color_variety = CASTi(_puyoType::Type::pupple)-CASTi(_puyoType::Type::red)+1;
    vector<bool> used(color_variety,false);
    vector<_puyoType::Type> colors;
    for(int c = CASTi(_puyoType::Type::red) ; c <= CASTi(_puyoType::Type::pupple) ; ++c)
        colors.push_back(static_cast<_puyoType::Type>(c));
    while(color_count > 0)
    {
        uniform_int_distribution<> dist(0,color_variety-1);
        const int idx = dist(gen);
        if(used[idx])
            continue;
        used[idx] = true;
        new_type_list.push_back(puyoType(make_unique<puyoColor>(colors[idx])));
        --color_count;
    }
////// 처음에 같은 색이 나올 수 없도록 함.
    while(new_types.empty()) 
    {
        get_new_puyos(1);
        if(new_types[0].first != new_types[0].second || new_types[0].second != new_types[1].first || new_types[1].first != new_types[1].second)
            break;
        new_types.clear();
    }
//////플레이어 기본 설정
    for(const auto& player : players)
    {
        player->get_board().set_spawn_pos(PLAYPUYO_IN_BOARD_SPAWN_POS);
        player->controll_vanish().set_condition(PUYO_VANISH_CONDITION);
        player->give_new_puyos(get_new_puyos(player->get_new_puyo_count()),gravity_value,stay_value);
        player->controll_future().update(player->get_board(),player->get_puyo());
    }
    pstate = puyoPhaseStatement(players.size());
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
        case Mode::frozen :
            curr_mode = make_unique<puyoModeFrozen>(get_player_count());
            break;
        case Mode::NONE : 
            throw runtime_error("curr mode ptr is nullptr");
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////

int puyoPhase::proceed_play(const unique_ptr<puyoPlayer>& player)
{
    int added_score = 0;
    auto& board = player->get_board();
    auto& cf = player->controll_future();
    auto& puyo = player->get_puyo();
    const int player_num = player->get_player_num();

    cf.fall(board);
    puyo.gravity_let(board);
    puyo.act_let(board);

    if(puyo.down())
        ++added_score;
    else if(puyo.dropped(board))
    {
        added_score += player->controll_score().get_drop_score(cf.get());

        auto& co = player->controll_obstuct();
        auto& cg = player->controll_gravity();
        cg.add(puyo.to_gravity_puyo(board));
        player->give_new_puyos(this->get_new_puyos(player->get_new_puyo_count()),gravity_value,stay_value);
        
        cf.update(board,player->get_puyo());
        player->signal_puyo_drop();
        co.approve_spawn();
        pstate.set_phase(player_num,puyoPhaseStatement::Phase::gravity);
    }
    return added_score;
}
int puyoPhase::proceed_gravity(const unique_ptr<puyoPlayer>& player)
{
    int added_score = 0;
    auto& board = player->get_board();
    auto& cg = player->controll_gravity();
    const int player_num = player->get_player_num();

    cg.gravity(board);
    if(cg.empty())
    {             
        auto& cv = player->controll_vanish();
        auto& cs = player->controll_score();
        const auto& [puyo_count, link_count, color_count, temp_energy_puyos] = cv.to_vanish_puyo(board); 
        cs.add_puyo_count(puyo_count);
        cs.add_link_count(link_count);
        cs.add_color_count(color_count);
        player->controll_energy().add_temp(temp_energy_puyos);
        if(cv.empty()) //파괴할 뿌요가 없으면
        {
            auto& co = player->controll_obstuct();
            if(co.spawn_approved())
            {
                cg.add(co.to_gravity_puyo(board,calc.get_obstruct_puyo_for_dropping(co.get())));
                co.disapprove_spawn();
            }
            else
            {
                pstate.set_phase(player_num,puyoPhaseStatement::Phase::play);
                pstate.delay(player_num,PHASE_SET_TICK);
                cs.reset_chain_count();
            }
        }
        else
        {
            cs.add_chain_count(board);
            added_score += calc.get_add_score(cs.get_puyo_count(),cs.get_chain_count(),cs.get_link_count(),cs.get_color_count());
            pstate.set_phase(player_num,puyoPhaseStatement::Phase::vanish);
        }
    }
    return added_score;
}
int puyoPhase::proceed_vanish(const unique_ptr<puyoPlayer>& player)
{
    int added_score = 0;
    auto& board = player->get_board();
    auto& cv = player->controll_vanish();
    const int player_num = player->get_player_num();

    cv.vanish(board);
    if(cv.empty())
    { 
        auto& cg = player->controll_gravity();
        auto& co = player->controll_obstuct();
        cg.add(board.to_gravity_puyo()); 
        if(cg.empty()) //파괴 후, 드롭할 뿌요가 없으면
        {
            auto& cs = player->controll_score();
            if(board.all_cleared())
                added_score += calc.get_all_cleared_score();//올클리어 보너스
            pstate.set_phase(player_num,puyoPhaseStatement::Phase::play);
            pstate.delay(player_num,PHASE_SET_TICK);
            cs.reset_chain_count();
        }
        else
            pstate.set_phase(player_num,puyoPhaseStatement::Phase::gravity);
    }
    return added_score;
}

void puyoPhase::manage_obstruct(const std::unique_ptr<puyoPlayer>& player, int added_score)
{
    if(players.size() == 1)
        throw runtime_error("Obstruct puyo spawn is prohibited in Solo");

    auto& board = player->get_board();
    auto& ce = player->controll_energy();
    auto& co = player->controll_obstuct();
    
    co.add_opp(calc.to_obstruct_puyo(added_score));
    if(!co.empty_opp()) 
    {
        auto& cv = player->controll_vanish();
        if(cv.empty())
        {
            const int player_num = player->get_player_num(), opposite = player->get_opposite();
            const int opp = calc.get_opposite_obstruct_puyo_count(co.get(),co.get_opp());

            const int to_player_num = (co.get() > 0) ? player_num : opposite;
            ce.to_energy_puyo(player_num,to_player_num);//에너지 뿌요 생성

            co.add(-co.get_opp());
            co.clear_opp();
            players[opposite]->controll_obstuct().add(opp);
        }
    } 
    else
        ce.clear_temp(); 
}
void puyoPhase::manage_game_end(const std::unique_ptr<puyoPlayer>& player)
{
    if(!game_end_asked())
    {
        if(player->get_score() == SCORE_UPPER-1)
        {
            ask_end_game();
            set_win_player_num(player->get_player_num());
        }
        else if(!player->get_board().spawn_able())
        {
            ask_end_game();
            set_win_player_num(player->get_opposite());
        }
    }
    else if(pstate.is_phase(win_player_num^1,puyoPhaseStatement::Phase::play))//게임 종료
        end_game(); 
}

void puyoPhase::proceed_event(const unique_ptr<puyoPlayer>& player)
{   
    auto& board = player->get_board();
    for(const auto state : board.update())
        switch(state)
        {
            case _puyoType::typeState::exploded :
            {
                const auto bsize = board.get_size();
                set_signal(puyoModeSignal::bomb_explode);
                for(size_t i = 0 ; i < bsize.r ; ++i)
                    for(size_t j = 0 ; j < bsize.c ; ++j)
                        if(!board.empty(POSi(j, i)))
                            player->controll_energy().add_temp(
                        player->controll_vanish().to_vanish_puyo_each(
                            board,{POSf(j,i),board.get_puyo(POSi(j, i)), puyoGameConstant::BOARD_BASIC_VANISH_TICK}));                                                 
                pstate.set_phase(player->get_player_num(),puyoPhaseStatement::Phase::vanish);
                ask_end_game();
                set_win_player_num(player->get_opposite());
                break;
            }
            default :
                break;
        }
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
        curr_mode->proceed_mode(*this, player);
        proceed_event(player);

        player->controll_energy().fly(board);
        int added_score = 0;
        switch(pstate.get_phase(player_num))
        {
            case puyoPhaseStatement::Phase::play :
                pstate.wait(player_num);
                if(pstate.delayed(player_num))
                    break;
                added_score += proceed_play(player);
                break;
            case puyoPhaseStatement::Phase::gravity :
                added_score += proceed_gravity(player);
                break;

            case puyoPhaseStatement::Phase::vanish :
                added_score += proceed_vanish(player);
                break;
        };
        player->add_score(added_score);
        if(get_player_count() == 2)
            manage_obstruct(player,added_score);
        else
            player->controll_energy().clear_temp(); 
/////////게임 종료
        manage_game_end(player);
        if(game_ended())
            return;
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
int puyoPhase::get_color_count() const {return new_type_list.size();}
void puyoPhase::add_new_type(const puyoType& type){new_type_list.push_back(type);}
void puyoPhase::remove_new_type(){new_type_list.pop_back();}

Mode puyoPhase::get_mode_type() const {return mode_type;}

int puyoPhase::get_win_player_num() const
{
    if(players.size() == 1)
        return NO_WINNER;//이긴 사람 없음 == 솔로 플레이
    return win_player_num;
}
void puyoPhase::set_win_player_num(int num){win_player_num = num;}

puyoPhaseStatement& puyoPhase::get_pstate(){return pstate;}