#include "puyoPage/pages/gamePage/puyoBoard/puyoBoardControll/puyoBoardGravityControll.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoAction/puyoPuyoGravity.hpp"

#include <algorithm>

using namespace std;

puyoBoardGravityControll::puyoBoardGravityControll()
{
    gravity_puyo_is_out_of_board = false;
}

void puyoBoardGravityControll::add(PUYO_INFO puyo) // std::move
{
    gravity_puyos.push_back(
        puyoPuyo(std::get<0>(puyo),std::get<1>(puyo),
        make_unique<puyoPuyoGravity>(std::get<2>(puyo))));
    gravity_puyos.back().let();    
}
void puyoBoardGravityControll::add(vector<PUYO_INFO> puyos) // std::move
{
    for(const auto& puyo : puyos)
        add(puyo);
}
const vector<puyoPuyo> &puyoBoardGravityControll::get() { return gravity_puyos;}

void puyoBoardGravityControll::gravity(puyoBoard& board)
{
    if(gravity_puyo_is_out_of_board)
        return;
    for(int i = 0 ; i < gravity_puyos.size(); )
    {
        if(gravity_puyos[i].acting())
            gravity_puyos[i].act_let(board);

        if(!gravity_puyos[i].acting())
        {
            const auto[x,y] = gravity_puyos[i].get_pos();
            const auto pos = POSi(round(x), round(y));
            if(!board.in(pos))
            {
                gravity_puyo_is_out_of_board = true; // 배치할 뿌요가 범위를 나감
                break;
            }
            else if(board.empty(pos))
                board.insert_puyo(gravity_puyos[i].get_type(), pos);

            std::swap(gravity_puyos[i],gravity_puyos.back());
            gravity_puyos.pop_back();
        }
        else
            ++i;
    }
}

bool puyoBoardGravityControll::empty() const { return gravity_puyos.empty(); }
bool puyoBoardGravityControll::out() const { return gravity_puyo_is_out_of_board; }