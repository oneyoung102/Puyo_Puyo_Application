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
{
    std::uniform_int_distribution<> dist(0, player_count-1);
    bomb_have_player_num = dist(gen);
}
void puyoModeBomb::proceed_mode(puyoPhase& phase, const puyoPlayer& player)
{
    if(bomb_have_player_num != player.get_player_num())
        return;

    auto& board = player.get_board();
    if(bomb_is_spawned)
    { 
        if(board.controll_score().get_chain_count() < BOMB_DISSOLVE_CHAIN)// 폭탄 해체
            return;

        auto& cv = board.controll_vanish();
        const auto bsize = board.get_size();
        for(int r = bsize.r-1 ; r >= 0 ; --r)//효율적으로 아래에서부터 찾음
        {
            const auto puyo = board.get_puyo(POSs(bomb_c, r));
            if(puyo != puyoType(P_BOMB(0)))
                continue;
            cv.to_vanish_puyo_each(board,{POSf(bomb_c,r),puyo,BOMB_VANISH_TICK});
            phase.get_pstate().set_phase(bomb_have_player_num,puyoPhaseStatement::Phase::vanish);
            break;
        }
        bomb_is_spawned = false;

        if(phase.get_player_count() == 1)//2인 플레이일 때만 넘김
            return;
        const int opposite = player.get_opposite();
        phase.get_players()[opposite]
        ->get_board()
        .controll_obstuct()
        .add(player.get_board().controll_obstuct().get()); // 상대에게 넘길 방해 뿌요 두 배
            bomb_have_player_num = opposite;
    }
    else if(phase.get_pstate().is_phase(bomb_have_player_num, puyoPhaseStatement::Phase::play))//폭탄 소환
    {
        auto& cg = board.controll_gravity();
        std::uniform_int_distribution<> dist(0, board.get_size().c-1);
        bomb_c = dist(gen);
        cg.add({POSf(bomb_c,OBSTRUCT_PUYO_SPAWN_Y), puyoType(P_BOMB(BOMB_MAX_TICK)), BOARD_FALL_GRAVITY_TICK});
        bomb_is_spawned = true;
        phase.set_signal(puyoModeSignal::bomb_fused);
        phase.get_pstate().set_phase(bomb_have_player_num,puyoPhaseStatement::Phase::gravity);
    }
}