#include "puyoPage/pages/gamePage/puyoPhase/puyoMode/puyoModeBomb.hpp"

#include "puyoPage/pages/gamePage/puyoPhase/puyoPhaseStatement.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/puyoType.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include "puyoPage/pages/gamePage/puyoPhase/puyoPhase.hpp"
#include "puyoPage/pages/gamePage/puyoPlayer/puyoPlayer.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include <random>

using namespace std;
using namespace puyoGameConstant;


puyoModeBomb::puyoModeBomb(int player_count)
    : gen(random_device()())
    , bomb_is_spawned(false)
    , bomb_is_exploded(false)
{
    std::uniform_int_distribution<> dist(0, player_count-1);
    bomb_have_player_num = dist(gen);
}
void puyoModeBomb::proceed_mode(puyoPhase& phase, const puyoPlayer& player)
{
    if(bomb_have_player_num != player.get_player_num())
        return;
    auto& board = player.get_board();
    auto& cv = board.controll_vanish();
    auto& cs = board.controll_score();
    auto& cg = board.controll_gravity();

    const auto bsize = board.get_size();
    const int opposite = bomb_have_player_num^1;

    if(bomb_is_exploded)
    {
        if(cv.empty())
        {
            phase.end_game();
            phase.set_win_player_num(opposite);
        }
        return;
    }
    else if(bomb_is_spawned)
    {
        for(int r = bsize.r-1 ; r >= 0 ; --r)//효율적으로 아래에서부터 찾음
        {
            auto puyo = board.get_puyo(POSs(bomb_c, r));
            if(puyo != puyoType(P_BOMB(0)))
                continue;
            if(puyo.is_exploded())//폭탄 터짐 종료
            {
                bomb_is_exploded = true;
                phase.set_signal(puyoModeSignal::bomb_explode);
                for(size_t i = 0 ; i < bsize.r ; ++i)
                    for(size_t j = 0 ; j < bsize.c ; ++j)
                        if(!board.empty(POSi(j, i)))
                            cv.to_vanish_puyo_each(board,{POSf(j,i),board.get_puyo(POSi(j, i)), BOARD_BASIC_VANISH_TICK});                                                 
                phase.get_pstate().set_phase(bomb_have_player_num,puyoPhaseStatement::Phase::vanish);
            }
            else if(board.controll_score().get_chain_count() >= BOMB_DISSOLVE_CHAIN)// 폭탄 해체
            {
                bomb_is_spawned = false;
                cv.to_vanish_puyo_each(board,{POSf(bomb_c,r),puyo,BOMB_VANISH_TICK});
                phase.get_players()[opposite]
                ->get_board()
                .controll_obstuct()
                .add(player.get_board().controll_obstuct().get());
                if(phase.get_player_count() == 2)//2인 플레이일 때만 넘김
                    bomb_have_player_num = opposite;
            }
            else if(cv.empty() && cg.empty())//폭탄 진행
                puyo.proceed_bomb();
            break;
        }
    }
    else if(cv.empty() && cg.empty())//폭탄 소환
    {
        std::uniform_int_distribution<> dist(0, board.get_size().x-1);
        bomb_c = dist(gen);
        cg.add({POSf(bomb_c,OBSTRUCT_PUYO_SPAWN_Y), puyoType(P_BOMB(BOMB_MAX_TICK)), BOARD_FALL_GRAVITY_TICK});
        bomb_is_spawned = true;
        phase.set_signal(puyoModeSignal::bomb_fused);
    }
}