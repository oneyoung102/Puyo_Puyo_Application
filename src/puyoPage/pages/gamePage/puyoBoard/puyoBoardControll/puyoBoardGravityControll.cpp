#include "puyoPage/pages/gamePage/puyoBoard/puyoBoardControll/puyoBoardGravityControll.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"

using namespace std;

puyoBoardGravityControll::puyoBoardGravityControll()
{
    gravity_puyo_is_out_in_board = false;
}

void puyoBoardGravityControll::push_gravity_puyo(puyoGravityPuyo &&ptp) // std::move
{
    gravity_puyos.push_back(std::move(ptp));
}
void puyoBoardGravityControll::push_gravity_puyo(vector<puyoGravityPuyo> &&ptp_v) // std::move
{
    for (auto &&ptp : ptp_v)
        push_gravity_puyo(std::move(ptp));
}
vector<puyoGravityPuyo> &puyoBoardGravityControll::get_gravity_puyos() { return gravity_puyos;}

void puyoBoardGravityControll::gravity_gravity_puyos(puyoBoard& board)
{
    for (int i = 0; i < gravity_puyos.size();)
    {
        if (gravity_puyos[i].gravity_stopped())
        {
            if (!gravity_puyos[i].deploy_puyo(board))
                gravity_puyo_is_out_in_board = true; // 배치할 뿌요가 범위를 나감
            std::swap(gravity_puyos[i], gravity_puyos.back());
            gravity_puyos.pop_back();
        }
        else
        {
            gravity_puyos[i].gravity_let(board);
            ++i;
        }
    }
}
void puyoBoardGravityControll::find_gravity_puyo(puyoBoard& board)
{
    const auto[board_r, board_c] = board.get_board_size();
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
                    push_gravity_puyo(std::move(puyoGravityPuyo(i, j, puyo, puyoGameConstant::BOARD_FALL_GRAVITY_TICK)));
                    board.remove_puyo(j, i);
                    continue;
                }
            }
            else
                push = true;
        }
    }
}

bool puyoBoardGravityControll::gravity_puyo_empty() { return gravity_puyos.empty(); }
bool puyoBoardGravityControll::gravity_puyo_is_out() { return gravity_puyo_is_out_in_board; }