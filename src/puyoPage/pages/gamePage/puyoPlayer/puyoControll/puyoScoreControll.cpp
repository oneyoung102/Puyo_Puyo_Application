#include "puyoPage/pages/gamePage/puyoPlayer/puyoControll/puyoScoreControll.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include "puyoTool/puyoCast.hpp"
#include <algorithm>

using namespace std;
using namespace puyoGameConstant;

puyoScoreControll::puyoScoreControll()
    : puyo_count(0)
    , chain_count(0)
    , link_count(vector<int>())
    , color_count(set<puyoType::Type>())
{
    set_obstruct_puyo_rate();
    set_all_cleared_obstruct_puyo();
}

 int puyoScoreControll::get_drop_score(const vector<puyoPuyo>& future_puyos, const puyoPlayPuyo& play_puyo) const
 {
    int drop_score = 0;
    for(const auto& future_puyo : future_puyos)
        drop_score += future_puyo.get_pos().y;

    const auto& [pos1,pos2] = play_puyo.get_pos();
    drop_score -= pos1.y + pos2.y;
    
    return drop_score/max(1,CASTi(future_puyos.size()));
 }

int puyoScoreControll::get_chain_count() const { return chain_count; }
void puyoScoreControll::add_chain_count() {++chain_count;}
void puyoScoreControll::reset_chain_count() { chain_count = 0; }

void puyoScoreControll::add_puyo_count(int count){puyo_count += count;}

void puyoScoreControll::add_link_count(int count){link_count.push_back(count);}
void puyoScoreControll::add_link_count(vector<int>&& counts){link_count.insert(link_count.end(), counts.begin(), counts.end());}

void puyoScoreControll::add_color_count(puyoType::Type type){color_count.insert(type);}
void puyoScoreControll::add_color_count(vector<puyoType::Type>&& types){color_count.insert(types.begin(), types.end());}

int puyoScoreControll::get_add_score()
{
    int accum = 0;
    for(const int link : link_count)
        accum += LINK_BONUS[CASTs(min(link,CASTi(LINK_BONUS.size())-1))];
    
    const int score = puyo_count*(max(
                CHAIN_BONUS[chain_count]
                +accum
                +COLOR_BONUS[min(color_count.size(),COLOR_BONUS.size()-1)]
                ,1))*10;

    color_count.clear();
    link_count.clear();
    puyo_count = 0;

    return score;
}

int puyoScoreControll::get_opposite_obstruct_puyo(int self, int opp) const {return max(0,opp-self);}
int puyoScoreControll::to_obstruct_puyo(int score) const {return score/obstruct_puyo_rate;}

void puyoScoreControll::set_obstruct_puyo_rate(int value){obstruct_puyo_rate = max(value,1);}
void puyoScoreControll::set_all_cleared_obstruct_puyo(int value){all_cleared_obstruct_puyo = value;}
int puyoScoreControll::get_all_cleared_score() const{return all_cleared_obstruct_puyo*obstruct_puyo_rate;}
int puyoScoreControll::get_obstruct_puyo_for_dropping(int obstruct_puyo) const {return min(obstruct_puyo,30);}//30개가 넘으면 30개 단위로 떨어뜨림
