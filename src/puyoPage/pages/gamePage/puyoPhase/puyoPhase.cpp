#include "puyoPage/pages/gamePage/puyoPhase/puyoPhase.hpp"
#include "puyoPage/pages/gamePage/puyoPhase/puyoMode/puyoModeBlocks.hpp"
#include "puyoPage/pages/gamePage/puyoPhase/puyoMode/puyoModeBomb.hpp"
#include "puyoPage/pages/gamePage/puyoPhase/puyoMode/puyoModeCharged.hpp"
#include "puyoPage/pages/gamePage/puyoPhase/puyoMode/puyoModeFrozen.hpp"
#include "puyoPage/pages/gamePage/puyoPhase/puyoMode/puyoModeSpeed.hpp"

#include "puyoPage/pages/gamePage/puyoPhase/puyoPhaseAsset/puyoPhaseControll.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoPlayPuyo/puyoPlayPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoAction/puyoPuyoGravity.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoAction/puyoPuyoVanish.hpp"

#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/puyoType.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/puyoType.hpp"

#include "puyoPage/puyoPageManager/puyoPageSignal.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"

#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoPhase/puyoPhaseAsset/puyoScoreCalc.hpp"

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

void puyoPhase::create_new_playpuyo(int count)
{
    if(new_puyo_pool.empty())
        throw runtime_error("new type list is empty, so can't take new puyos");
    while(new_puyos.size() <= count+DISPLAYED_NEXT_PUYO_COUNT) //다음에 나올 뿌요를 보여주기 위해 NEXT_PUYO_COUNT_DISPLAY개수 더 더하기
    {
        uniform_int_distribution<> dist1(0, new_puyo_pool.size()-1);
        uniform_int_distribution<> dist2(0, new_puyo_pool.size()-1);
        new_puyos.push_back({
            new_puyo_pool[dist1(gen)],
            new_puyo_pool[dist2(gen)]});
    }
}

PLAYPUYO puyoPhase::get_new_playpuyo(int count)
{
    create_new_playpuyo(count);
    return new_puyos.toss(count);
}

const decltype(puyoPhase::new_puyos)& puyoPhase::get_new_puyos() const {return new_puyos;}
decltype(puyoPhase::new_puyos)& puyoPhase::get_new_puyos() {return new_puyos;}

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
    const int color_variety = CASTi(puyoType::Type::pupple)-CASTi(puyoType::Type::red)+1;
    vector<bool> used(color_variety,false);
    vector<puyoType::Type> colors;
    for(int c = CASTi(puyoType::Type::red) ; c <= CASTi(puyoType::Type::pupple) ; ++c)
        colors.push_back(static_cast<puyoType::Type>(c));
    while(color_count > 0)
    {
        uniform_int_distribution<> dist(0,color_variety-1);
        const int idx = dist(gen);
        if(used[idx])
            continue;
        used[idx] = true;
        new_puyo_pool.push_back(puyoPuyo(POSs(),make_unique<puyoColor>(colors[idx])));
        --color_count;
    }
////// 처음에 같은 색이 나올 수 없도록 함.
    while(new_puyos.empty()) 
    {
        create_new_playpuyo(1);
        if(new_puyos.view(0)[0] != new_puyos.view(0)[1]
        || new_puyos.view(0)[1] != new_puyos.view(1)[0]
        || new_puyos.view(1)[0] != new_puyos.view(1)[1])
            break;
        new_puyos.clear();
    }
//////플레이어 기본 설정
    for(auto& player : players)
    {
        player.get_board().set_spawn_pos(PLAYPUYO_IN_BOARD_SPAWN_POS);
        player.controll_vanish().set_condition(PUYO_VANISH_CONDITION);
        player.give_new_puyos(std::move(get_new_playpuyo(player.get_new_puyo_count())),gravity_value,stay_value);
        player.controll_future().spawn(player.get_board(),player.get_puyo());
    }
    phase_controll = puyoPhaseControll(players.size());
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
        case Mode::charged :
            curr_mode = make_unique<puyoModeCharged>(get_players());
            break;
        case Mode::blocks :
            curr_mode = make_unique<puyoModeBlocks>(get_players());
            break;
        case Mode::NONE : 
            throw runtime_error("curr mode ptr is nullptr");
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////

int puyoPhase::proceed_play(puyoPlayer& player)
{
    const auto& puyo = player.get_puyo();
    phase_controll.act_play_puyo(player);
    if(puyo.down())
        return 1;
    else if(puyo.dropped())
    {
        phase_controll.set_phase(player.get_player_num(),puyoPhaseControll::Phase::gravity);
        return phase_controll.do_after_puyo_dropped(player, get_new_playpuyo(player.get_new_puyo_count()),gravity_value,stay_value);
    }
    return 0;
}
int puyoPhase::proceed_gravity(puyoPlayer& player)
{
    if(phase_controll.act_gravity_puyos(player))
    {        
        const int player_num = player.get_player_num();
        auto& cs = player.controll_score();       
        if(phase_controll.test_and_prepare_vanish(player)) //사라질 뿌요가 없으면
        {
            if(!phase_controll.test_spawn_obstruct_puyo(player, calc.get_obstruct_puyo_for_dropping(player.controll_obstuct().get())))
            {
                phase_controll.set_phase(player_num,puyoPhaseControll::Phase::play);
                phase_controll.delay(player_num,PHASE_SET_TICK);
            }
        }
        else
        {
            phase_controll.set_phase(player_num,puyoPhaseControll::Phase::vanish);
            player.get_board().signal(puyoBoardSignal::chain);
            cs.add_chain_count();
            return calc.get_add_score(cs.get_puyo_count(),cs.get_chain_count(),cs.get_link_count(),cs.get_color_count());
        }
    }
    return 0;
}
int puyoPhase::proceed_vanish(puyoPlayer& player)
{
    const int player_num = player.get_player_num();
    if(phase_controll.act_vanish_puyos(player))
    { 
        if(phase_controll.test_and_prepare_gravity(player)) //파괴 후, 드롭할 뿌요가 없으면
        {
            phase_controll.set_phase(player_num,puyoPhaseControll::Phase::play);
            phase_controll.delay(player_num,PHASE_SET_TICK);

            if(player.get_board().all_cleared())
                return calc.get_all_cleared_score();//올클리어 보너스
        }
        else
            phase_controll.set_phase(player_num,puyoPhaseControll::Phase::gravity);
    }
    return 0;
}

void puyoPhase::manage_obstruct(puyoPlayer& player, int added_score)
{
    if(players.size() == 1)
        throw runtime_error("Obstruct puyo spawn is prohibited in Solo");

    auto& ce = player.controll_energy();
    auto& co = player.controll_obstuct();
    
    co.accumulate_score(added_score);
    if(player.controll_score().get_chain_count() >= 1) 
    {
        //방해뿌요 계산
        if(!player.controll_vanish().empty())
            return;
        const int obstruct_puyo = calc.to_obstruct_puyo(co.get_accumulated_score());
        if(obstruct_puyo > 0)
        {
            const int player_num = player.get_player_num(), opposite = player.get_opposite();
            const int opposite_obstruct_puyo_count = calc.get_opposite_obstruct_puyo(co.get(),obstruct_puyo);

            const int to_player_num = (co.get() > 0) ? player_num : opposite;
            ce.spawn(player_num, to_player_num);//에너지 뿌요 생성

            co.add(-obstruct_puyo);
            co.clear_accumulated_score();
            players[opposite].controll_obstuct().add(opposite_obstruct_puyo_count);
        }
        phase_controll.reset_all_chain(player);
    } 
    else
        ce.clear(); 
}
void puyoPhase::manage_game_end(puyoPlayer& player)
{
    if(!game_end_asked())
    {
        if(player.get_score() >= SCORE_UPPER-1)
        {
            ask_end_game();
            set_win_player_num(player.get_player_num());
        }
        else if(!player.get_board().spawn_able())
        {
            ask_end_game();
            set_win_player_num(player.get_opposite());
        }
    }
    else if(phase_controll.is_phase(win_player_num^1,puyoPhaseControll::Phase::play))//게임 종료
        end_game(); 
}

void puyoPhase::proceed_event(puyoPlayer& player)
{   
    auto& board = player.get_board();
    for(const auto state : board.update())
        switch(state)
        {
            case puyoType::typeState::exploded :
            {
                const auto& bsize = board.get_size();
                signal(puyoModeSignal::bomb_explode);
                for(size_t i = 0 ; i < bsize.r ; ++i)
                    for(size_t j = 0 ; j < bsize.c ; ++j)
                        if(!board.empty({j, i}))
                            player.controll_vanish().add(board.to_vanish_puyo({j,i}));                                                 
                phase_controll.set_phase(player.get_player_num(),puyoPhaseControll::Phase::vanish);
                ask_end_game();
                set_win_player_num(player.get_opposite());
                break;
            }
            default :
                break;
        }
}

void puyoPhase::proceed_game()
{
    for(auto& player : players)
    {
        const auto& board = player.get_board();
        const int player_num = player.get_player_num();
/////////////////봇이라면 행동
        if(player.is_bot())
            if(phase_controll.is_phase(player_num,puyoPhaseControll::Phase::play) && !phase_controll.delayed(player_num))
                player.act_bot_let(); 
/////////////////모드 진행
        curr_mode->proceed_mode(*this, player);
        proceed_event(player);

        player.controll_energy().fly(board);
        int added_score = 0;
        switch(phase_controll.get_phase(player_num))
        {
            case puyoPhaseControll::Phase::play :
                phase_controll.wait(player_num);
                if(phase_controll.delayed(player_num))
                    break;
                added_score += proceed_play(player);
                break;
            case puyoPhaseControll::Phase::gravity :
                added_score += proceed_gravity(player);
                break;

            case puyoPhaseControll::Phase::vanish :
                added_score += proceed_vanish(player);
                break;
        };
        player.add_score(added_score);
        if(get_player_count() == 2)
            manage_obstruct(player,added_score);
        else
            player.controll_energy().clear(); 
/////////게임 종료
        manage_game_end(player);
        if(game_ended())
            return;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////

int puyoPhase::get_player_count() const {return players.size();}
vector<puyoPlayer>& puyoPhase::get_players(){return players;}
void puyoPhase::add_player(puyoPlayer&& player)
{
    if(players.size() == 2)
        throw runtime_error("Player count must be 1 or 2");
    players.push_back(std::move(player));
}
int puyoPhase::get_gravity_value() const {return gravity_value;}
void puyoPhase::set_gravity_value(int value){gravity_value = value;}
int puyoPhase::get_stay_value() const {return stay_value;}
void puyoPhase::set_stay_value(int value){stay_value = value;}
int puyoPhase::get_color_count() const {return new_puyo_pool.size();}
void puyoPhase::add_new_type(const puyoPuyo& type){new_puyo_pool.push_back(type);}
void puyoPhase::remove_new_type(){new_puyo_pool.pop_back();}

Mode puyoPhase::get_mode_type() const {return mode_type;}

int puyoPhase::get_win_player_num() const
{
    if(players.size() == 1)
        return NO_WINNER;//이긴 사람 없음 == 솔로 플레이
    return win_player_num;
}
void puyoPhase::set_win_player_num(int num){win_player_num = num;}

puyoPhaseControll& puyoPhase::controll_phase(){return phase_controll;}