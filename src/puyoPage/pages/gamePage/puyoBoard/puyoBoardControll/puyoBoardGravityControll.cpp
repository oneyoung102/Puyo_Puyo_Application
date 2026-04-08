#include "puyoPage/pages/gamePage/puyoBoard/puyoBoardControll/puyoBoardGravityControll.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoAction/puyoPuyoGravity_temp.hpp"

using namespace std;

puyoBoardGravityControll::puyoBoardGravityControll()
{
    gravity_puyo_is_out_in_board = false;
}

void puyoBoardGravityControll::add(PUYO_INFO puyo) // std::move
{
    gravity_puyos.push_back(
        std::move(puyoPuyo(std::get<0>(puyo),std::get<1>(puyo),std::get<2>(puyo),
        make_unique<puyoPuyoGravity_temp>(std::get<3>(puyo)))));
    gravity_puyos.back().let();
}
void puyoBoardGravityControll::add(vector<PUYO_INFO> puyos) // std::move
{
    for (const auto& puyo : puyos)
        add(puyo);
}
vector<puyoPuyo> &puyoBoardGravityControll::get() { return gravity_puyos;}

void puyoBoardGravityControll::gravity(puyoBoard& board)
{
    for(int i = 0; i < gravity_puyos.size();)
        if(!gravity_puyos[i].acting())
        {
            const auto[x,y] = gravity_puyos[i].get_pos();
            const int ix = round(x), iy = round(y);
            const puyoType type = gravity_puyos[i].get_type();
            if (!board.in(iy,ix))
                gravity_puyo_is_out_in_board = true; // 배치할 뿌요가 범위를 나감
            else if(board.get_puyo(iy,ix) == puyoType::blank)
                board.insert_puyo(type,iy,ix);

            std::swap(gravity_puyos[i], gravity_puyos.back());
            gravity_puyos.pop_back();
        }
        else
        {
            gravity_puyos[i].act_let(board);
            ++i;
        }
}
void puyoBoardGravityControll::find(puyoBoard& board)
{
    const auto[board_r, board_c] = board.get_size();
    for (int i = 0; i < board_c; ++i)
    {
        bool push = false;
        for (int j = board_r - 1; j >= 0; --j) // 아래에 있는 뿌요가 먼저 오게
        {
            const puyoType puyo = board.get_puyo(j,i);
            if(puyo != puyoType::blank) 
            {
                if(push)
                {
                    add({i, j, puyo, puyoGameConstant::BOARD_FALL_GRAVITY_TICK});
                    board.remove_puyo(j, i);
                    continue;
                }
            }
            else
                push = true;
        }
    }
}

bool puyoBoardGravityControll::empty() { return gravity_puyos.empty(); }
bool puyoBoardGravityControll::out() { return gravity_puyo_is_out_in_board; }