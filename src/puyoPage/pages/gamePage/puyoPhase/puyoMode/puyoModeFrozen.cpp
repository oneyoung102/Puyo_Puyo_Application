#include "puyoPage/pages/gamePage/puyoPhase/puyoMode/puyoModeFrozen.hpp"

#include "puyoPage/pages/gamePage/puyoPhase/puyoPhase.hpp"
#include "puyoPage/pages/gamePage/puyoPlayer/puyoPlayer.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include <random>

using namespace std;
using namespace puyoGameConstant;

puyoModeFrozen::puyoModeFrozen(int play_count)
    : time(max(play_count,0),0)
    , gen(random_device{}())
{}
void puyoModeFrozen::proceed_mode(puyoPhase& phase, const puyoPlayer& player)
{
    const int player_num = player.get_player_num();
    ++time[player_num];
    if(time[player_num] < FREEZE_TICK)
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
        uniform_int_distribution<> dist1(0,freeze_able_col.size()-1);
        board.ref_puyo(POSs(freeze_able_col[dist1(gen)],r)).freeze();
        phase.set_signal(puyoModeSignal::freeze);
        break;
    }
    
    uniform_int_distribution<> dist2(0,100);
    const int prob = dist2(gen);
    if(prob < PROB_FREEZE_ONCE)  
        phase.get_new_types().back().first.freeze();
    if(PROB_FREEZE_ONCE-PROB_FREEZE_TWICE <= prob && prob < 2*PROB_FREEZE_ONCE-PROB_FREEZE_TWICE)
        phase.get_new_types().back().second.freeze();
}