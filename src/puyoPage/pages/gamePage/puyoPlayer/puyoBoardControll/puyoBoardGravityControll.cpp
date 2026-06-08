#include "puyoPage/pages/gamePage/puyoPlayer/puyoBoardControll/puyoBoardGravityControll.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoAction/puyoPuyoGravity.hpp"

#include <algorithm>

using namespace std;

puyoBoardGravityControll::puyoBoardGravityControll()
{}

void puyoBoardGravityControll::add(puyoPuyo&& puyo)
{
    gravity_puyos.push_back(std::move(puyo));
    gravity_puyos.back().let();    
}
void puyoBoardGravityControll::add(vector<puyoPuyo>&& puyos)
{
    for(auto& puyo : puyos)
        add(std::move(puyo));
}
const vector<puyoPuyo>& puyoBoardGravityControll::get() const { return gravity_puyos;}

void puyoBoardGravityControll::gravity(puyoBoard& board)
{
    for(size_t i = 0 ; i < gravity_puyos.size(); )
    {
        if(gravity_puyos[i].acting())
            gravity_puyos[i].act_let(board);

        if(!gravity_puyos[i].acting())
        {
            const auto[x,y] = gravity_puyos[i].get_pos();
            const auto& pos = POSi(round(x), round(y));
            if(board.in(pos) && board.empty(pos))
                board.insert_puyo(gravity_puyos[i], pos);
            
            std::swap(gravity_puyos[i],gravity_puyos.back());
            gravity_puyos.pop_back();
        }
        else
            ++i;
    }
}

bool puyoBoardGravityControll::empty() const { return gravity_puyos.empty(); }