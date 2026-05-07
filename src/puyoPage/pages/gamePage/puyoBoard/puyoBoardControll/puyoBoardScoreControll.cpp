#include "puyoPage/pages/gamePage/puyoBoard/puyoBoardControll/puyoBoardScoreControll.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"

using namespace std;

puyoBoardScoreControll::puyoBoardScoreControll()
    : puyo_count(0)
    , chain_count(0)
    , link_count(vector<int>())
    , color_count(set<_puyoType::Type>())
{}

int puyoBoardScoreControll::get_chain_count() { return chain_count; }
void puyoBoardScoreControll::add_chain_count(puyoBoard& board)
{
    board.set_signal(puyoBoardSignal::chain);
    ++chain_count;
}
void puyoBoardScoreControll::reset_chain_count() { chain_count = 0; }

int puyoBoardScoreControll::get_puyo_count() { return exchange(puyo_count, 0); }
void puyoBoardScoreControll::add_puyo_count(int count){puyo_count += count;}

vector<int> puyoBoardScoreControll::get_link_count()
{
    vector<int> temp = link_count;
    link_count.clear();
    return temp;
}
void puyoBoardScoreControll::add_link_count(int count){link_count.push_back(count);}
void puyoBoardScoreControll::add_link_count(const vector<int>& counts){link_count.insert(link_count.end(), counts.begin(), counts.end());}

int puyoBoardScoreControll::get_color_count()
{
    const int temp = color_count.size();
    color_count.clear();
    return temp;
}
void puyoBoardScoreControll::add_color_count(_puyoType::Type type){color_count.insert(type);}
void puyoBoardScoreControll::add_color_count(const vector<_puyoType::Type>& types){color_count.insert(types.begin(), types.end());}
