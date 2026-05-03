#include "puyoPage/pages/gamePage/puyoPhase/puyoPhaseStatement.hpp"
#include <cmath>
#include <vector>

using namespace std;


puyoPhaseStatement::puyoPhaseStatement(int player_count)
    : curr_phases(player_count,Phase::play)
    , delay_times(player_count,0)
{}

puyoPhaseStatement::Phase puyoPhaseStatement::get_phase(int player_num) const {return curr_phases[player_num];}
void puyoPhaseStatement::set_phase(int player_num, Phase phase){curr_phases[player_num] = phase;}
bool puyoPhaseStatement::is_phase(int player_num, Phase phase) const {return curr_phases[player_num] == phase;}

void puyoPhaseStatement::delay(int player_num, int time){delay_times[player_num] += time;}
void puyoPhaseStatement::wait(int player_num){delay_times[player_num] = fmax(delay_times[player_num]-1,0);}
bool puyoPhaseStatement::delayed(int player_num) const{return delay_times[player_num] > 0;}