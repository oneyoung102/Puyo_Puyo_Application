#pragma once

#include <vector>

class puyoPhaseStatement
{
    public :
        enum class Phase{
            play,
            gravity,
            vanish
        };
    private :
        std::vector<Phase> curr_phases;
        std::vector<int> delay_times;
    public :
        puyoPhaseStatement(int player_count = 0);
        
        Phase get_phase(int player_num) const;
        void set_phase(int player_num, Phase phase);
        bool is_phase(int player_num, Phase phase) const;

        void delay(int player_num, int time);
        void wait(int player_num);
        bool delayed (int player_num) const;
};