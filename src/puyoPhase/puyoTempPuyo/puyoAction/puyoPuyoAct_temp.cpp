#include "puyoPuyoAct_temp.hpp"

#include <tuple>
#include <cmath>

bool puyoPuyoAct_temp::is_acting(){return act_count != -1;}
puyoPuyoAct_temp::puyoPuyoAct_temp(int amount) : act_count_init(amount){act_count = -1;}
void puyoPuyoAct_temp::let_act(){if(!is_acting()) act_count = 0;}
void puyoPuyoAct_temp::halt_act(){act_count = -1;}
float puyoPuyoAct_temp::get_state(){return (float)act_count/act_count_init;}
