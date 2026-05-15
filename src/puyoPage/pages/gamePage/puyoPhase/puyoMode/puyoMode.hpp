#pragma once

#include <memory>

class puyoPhase;
class puyoPlayer;
class puyoMode
{
    public :
        virtual ~puyoMode() = default;
        virtual void proceed_mode(puyoPhase& phase, const std::unique_ptr<puyoPlayer>&  player) = 0;
};  