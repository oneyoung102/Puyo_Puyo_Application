#include <vector>
#include "puyoPage/pages/gamePage/puyoPhase/puyoScoreCalc.hpp"
#include "puyoTool/puyoCast.hpp"

using namespace std;

puyoScoreCalc::puyoScoreCalc()
{
    obstruct_puyo_rate = 70;
    all_cleared_obstruct_puyo = 30;
    chain_bonus = {0,0,8,16,32,64,96,128,160,192,224,256,288,320,352,384,416,448,480,512};
    link_bonus = {0,0,0,0,0,2,3,4,5,6,7,10}; // 11개 이상은 항상 10
    color_bonus = {0,0,3,6,12,24};
}
int puyoScoreCalc::get_add_score(int puyo, int chain, const vector<int>& link, int color)
{
    int accum = 0;
    for(const int i : link)
        accum += link_bonus[CASTs(min(i,CASTi(link_bonus.size())-1))];
    return puyo*(max(
                chain_bonus[chain]
                +accum
                +color_bonus[CASTs(min(color,CASTi(color_bonus.size())-1))]
                ,1))*10;
}

int puyoScoreCalc::get_opposite_obstruct_puyo_count(int self, int opp) {return max(0,opp-self);}
int puyoScoreCalc::to_obstruct_puyo(int score){return score/obstruct_puyo_rate;}

void puyoScoreCalc::set_obstruct_puyo_rate(int v){obstruct_puyo_rate = max(v,1);}
int puyoScoreCalc::get_all_cleared_score(){return all_cleared_obstruct_puyo*obstruct_puyo_rate;}
int puyoScoreCalc::get_obstruct_puyo_for_dropping(int obstruct_puyo){return min(obstruct_puyo,30);}//30개가 넘으면 30개 단위로 떨어뜨림