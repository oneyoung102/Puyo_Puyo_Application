#pragma once

class puyoPhase;

class puyoMode 
{
    public :
        virtual ~puyoMode() = default;
        virtual void proceed_mode(puyoPhase& phase) = 0;
};  