#include "puyoPage/pages/gamePage/puyoPhase/puyoMode/puyoModeBomb.hpp"

#include "puyoPage/pages/gamePage/puyoBoard/puyoType.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include "puyoPage/pages/gamePage/puyoPhase/puyoPhase.hpp"
#include "puyoPage/pages/gamePage/puyoPlayer/puyoPlayer.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include <random>

using namespace std;
using namespace puyoGameConstant;


puyoModeBomb::puyoModeBomb(int player_count)
    : gen(random_device()())
{
    std::uniform_int_distribution<> dist(0, player_count-1);
    bomb_have_player_num = dist(gen);
    bomb_is_spawned = false;
    bomb_c = -1;

}
void puyoModeBomb::proceed_mode(puyoPhase& phase, puyoPlayer& player)
{
    if(bomb_have_player_num != player.get_player_num())
        return;
    auto& board = player.get_board();
    auto& cv = board.controll_vanish();
    auto& cs = board.controll_score();
    auto& cg = board.controll_gravity();

    const auto[r,c] = board.get_size();
    const int opposite = bomb_have_player_num^1;
    if(bomb_is_spawned)
    {
        if(bomb_tick <= 0)//폭탄 터짐 종료
        {
            if(bomb_tick == 0)
            {
                phase.set_signal(puyoModeSignal::bomb_explode);
                for(int i = 0 ; i < r ; ++i)
                    for(int j = 0 ; j < c ; ++j)
                        if(board.get_puyo(i,j) != puyoType::blank)
                            cv.make_vanish(board,j,i,board.get_puyo(i,j), BOARD_BASIC_VANISH_TICK);                                                 
                bomb_tick = -1;
            }
            else if(cv.empty())
            {
                phase.end_game();
                phase.set_win_player_num(opposite);
            }
        }
        else if(board.controll_score().get_chain_count() >= BOMB_DISSOLVE_CHAIN)// 폭탄 해체
        {
            bomb_is_spawned = false;
            for(int i = r-1 ; i >= 0 ; --i)//효율적으로 아래에서부터 찾음
            {
                const auto puyo = board.get_puyo(i,bomb_c);
                if(puyoType::tiny_bomb <= puyo && puyo <= puyoType::danger_bomb)
                {
                    cv.make_vanish(board,bomb_c,i,puyo,BOMB_VANISH_TICK);
                    break;
                }
            }
            player.add_opposite_obstruct_puyo_count(player.get_opposite_obstruct_puyo_count());
            if(phase.get_player_count() == 2)//2인 플레이일 때만 넘김
                bomb_have_player_num = opposite;
        }
        else if(cv.empty() && cg.empty())//폭탄 진행
        {
            --bomb_tick;
            bool appearance_change = true;
            switch(bomb_tick)
            {
                case BOMB_UPDATED1 :
                    bomb_appearance = puyoType::mid_bomb;
                    break;
                case BOMB_UPDATED2 :
                    bomb_appearance = puyoType::big_bomb;
                    break;
                case BOMB_UPDATED3 :
                    bomb_appearance = puyoType::danger_bomb;
                    break;
                default :
                    appearance_change = false;
                    break;
            }
            if(appearance_change)
            {
                for(int i = r-1 ; i >= 0 ; --i)//효율적으로 아래에서부터 찾음
                {
                    const auto puyo = board.get_puyo(i,bomb_c);
                    if(puyoType::tiny_bomb <= puyo && puyo <= puyoType::danger_bomb)
                    {
                        board.insert_puyo(bomb_appearance,i,bomb_c);
                        break;
                    }
                }
            }
        }
    }
    else if(cv.empty() && cg.empty())//폭탄 소환
    {
        std::uniform_int_distribution<> dist(0, board.get_size().second-1);
        bomb_c = dist(gen);
        bomb_appearance = puyoType::tiny_bomb;
        cg.add({bomb_c, OBSTRUCT_PUYO_SPAWN_Y,bomb_appearance, BOARD_FALL_GRAVITY_TICK});
        bomb_tick = BOMB_MAX_TICK;
        bomb_is_spawned = true;
        phase.set_signal(puyoModeSignal::bomb_fused);
    }
}