#include <vector>

#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"

using namespace std;

puyoBoard::puyoBoard() : board_r(13), board_c(6), puyoObjectSignal()
{
    board = vector<vector<puyoType>>(board_r, vector<puyoType>(board_c, puyoType::blank));
}

POS puyoBoard::get_spawn_pos() const {return spawn_pos;}
void puyoBoard::set_spawn_pos(POS pos)
{
    spawn_pos = pos;
};

pair<int, int> puyoBoard::get_size() const {return make_pair(board_r, board_c);}
bool puyoBoard::in_row(int r) const { return 0 <= r && r < board_r; }
bool puyoBoard::in_col(int c) const { return 0 <= c && c < board_c; }
bool puyoBoard::in(int r, int c) const {return in_row(r) && in_col(c);} // 이건 행,열
bool puyoBoard::touched(int r, int c) const// 이건 행,열
{
    return r >= 0 && (!in(r,c) || !empty(r,c))
        || r < 0 && !in_col(c);
}

puyoType puyoBoard::get_puyo(int r, int c) const {return board[r][c];} // 이건 행,열
void puyoBoard::insert_puyo(puyoType puyo, int r, int c) {board[r][c] = puyo;} // 이건 행,열
void puyoBoard::remove_puyo(int r, int c) {board[r][c] = puyoType::blank;} // 이건 행,열

bool puyoBoard::empty() const
{
    for (const auto puyo : board.back())
        if (puyo != puyoType::blank)
            return false;
    return true;
}
bool puyoBoard::empty(int r, int c) const {return get_puyo(r,c) == puyoType::blank;}
bool puyoBoard::all_cleared(){
    if(!empty())
        return false;
    set_signal(puyoBoardSignal::all_cleared);
    return true;
}

vector<PUYO_INFO> puyoBoard::to_gravity_puyo()
{
    vector<PUYO_INFO> gravity_puyos;
    for(int j = 0 ; j < board_c; ++j)
    {
        bool floating = false;
        for(int i = board_r-1 ; i >= 0 ; --i)
        {
            if(empty(i,j))
                floating = true;
            else if(floating)
            {
                gravity_puyos.push_back({POS(j,i), get_puyo(i,j), puyoGameConstant::BOARD_FALL_GRAVITY_TICK});
                remove_puyo(i,j);
                continue;
            }
        }
    }
    return std::move(gravity_puyos);
}

puyoBoardEnergyControll& puyoBoard::controll_energy(){return energy_controll;}
puyoBoardGravityControll& puyoBoard::controll_gravity(){return gravity_controll;}
puyoBoardScoreControll& puyoBoard::controll_score(){return score_controll;}
puyoBoardObstructControll& puyoBoard::controll_obstuct(){return obstuct_controll;}
puyoBoardVanishControll& puyoBoard::controll_vanish(){return vanish_controll;}
puyoBoardFutureControll& puyoBoard::controll_future(){return future_controll;}



