#include "puyoPage/pages/gamePage/puyoPlayer/puyoControll/puyoScoreControll.hpp"
#include "puyoTool/puyoCast.hpp"

using namespace std;

puyoScoreControll::puyoScoreControll()
    : puyo_count(0)
    , chain_count(0)
    , link_count(vector<int>())
    , color_count(set<puyoType::Type>())
{}

 int puyoScoreControll::get_drop_score(const vector<puyoPuyo>& future_puyos, const puyoPlayPuyo& play_puyo) const
 {
    int drop_score = 0;
    for(const auto& future_puyo : future_puyos)
        drop_score += future_puyo.get_pos().y;

    const auto& [pos1,pos2] = play_puyo.get_pos();
    drop_score -= pos1.y + pos2.y;
    
    return drop_score/max(1,CASTi(future_puyos.size()));
 }

int puyoScoreControll::get_chain_count() const{ return chain_count; }
void puyoScoreControll::add_chain_count() {++chain_count;}
void puyoScoreControll::reset_chain_count() { chain_count = 0; }

int puyoScoreControll::get_puyo_count() { return exchange(puyo_count, 0); }
void puyoScoreControll::add_puyo_count(int count){puyo_count += count;}

vector<int> puyoScoreControll::get_link_count(){return exchange(link_count,{});}
void puyoScoreControll::add_link_count(int count){link_count.push_back(count);}
void puyoScoreControll::add_link_count(vector<int>&& counts){link_count.insert(link_count.end(), counts.begin(), counts.end());}

int puyoScoreControll::get_color_count()
{
    const int temp = color_count.size();
    color_count.clear();
    return temp;
}
void puyoScoreControll::add_color_count(puyoType::Type type){color_count.insert(type);}
void puyoScoreControll::add_color_count(vector<puyoType::Type>&& types){color_count.insert(types.begin(), types.end());}
