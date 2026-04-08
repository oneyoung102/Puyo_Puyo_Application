#include "puyoPuyoAct_temp.hpp"

bool puyoPuyoAct_temp::acting(){return act_count != -1;}
puyoPuyoAct_temp::puyoPuyoAct_temp(int amount) : act_count_init(amount){act_count = -1;}
void puyoPuyoAct_temp::let(){if(!acting()) act_count = 0;}
void puyoPuyoAct_temp::halt(){act_count = -1;}
float puyoPuyoAct_temp::get_state(){return (float)act_count/act_count_init;}
int puyoPuyoAct_temp::get_act_count_init(){return act_count_init;}
