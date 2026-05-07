#include "puyoPage/pages/gamePage/puyoPhase/puyoMode/puyoModeFrozen.hpp"

#include "puyoPage/pages/gamePage/puyoPhase/puyoPhase.hpp"
#include "puyoPage/pages/gamePage/puyoPlayer/puyoPlayer.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include <random>

using namespace std;

puyoModeFrozen::puyoModeFrozen(int play_count)
    : time(max(play_count,0),0)
    , gen(random_device{}())
{}
void puyoModeFrozen::proceed_mode(puyoPhase& phase, const puyoPlayer& player)
{
    const int player_num = player.get_player_num();
    ++time[player_num];
    if(time[player_num] < puyoGameConstant::FREEZE_TICK)
        return;
    time[player_num] = 0;
    auto& board = player.get_board();
    const auto bsize = board.get_size();
    for(int r = bsize.r-1 ; r >= 0 ; --r)
    {
        vector<int> freeze_able_col;
        for(int c = 0 ; c < bsize.c ; ++c)
        {
            const auto pos = POSs(c,r);
            if(!board.empty(pos) && !board.get_puyo(pos).is_frozen())
                freeze_able_col.push_back(c);
        }
        if(freeze_able_col.empty())
            continue;
        uniform_int_distribution<> dist(0,freeze_able_col.size()-1);
        board.ref_puyo(POSs(freeze_able_col[dist(gen)],r)).freeze();
        break;
    }
}