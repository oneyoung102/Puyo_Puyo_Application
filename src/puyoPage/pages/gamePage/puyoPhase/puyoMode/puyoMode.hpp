#pragma once

class puyoPhase;
class puyoPlayer;

class puyoMode
{
    public :
        virtual ~puyoMode() = default;
        virtual void proceed_mode(puyoPhase& phase, puyoPlayer& player) = 0;
};  