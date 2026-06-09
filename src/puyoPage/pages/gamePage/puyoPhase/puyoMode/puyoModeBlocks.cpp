#include "puyoPage/pages/gamePage/puyoPhase/puyoMode/puyoModeBlocks.hpp"

#include "puyoPage/pages/gamePage/puyoPhase/puyoPhase.hpp"
#include "puyoPage/pages/gamePage/puyoPlayer/puyoPlayer.hpp"

puyoModeBlocks::puyoModeBlocks(const std::vector<std::unique_ptr<puyoPlayer>>& players)
{
    for(const auto& player : players)
    {
        auto& board = player->get_board();
        for(size_t i = 0 ; i < 5 ; ++i)
            board.insert_puyo(puyoPuyo(POSi(i,9),P_WALL)); //테스트
    }
}
void puyoModeBlocks::proceed_mode(puyoPhase& phase, const std::unique_ptr<puyoPlayer>& player){}