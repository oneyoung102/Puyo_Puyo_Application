#include <vector>

#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoType.hpp"
#include "puyoPage/pages/gamePage/puyoTempPuyo/puyoEnergyPuyo.hpp"

#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

using namespace std;
using namespace puyoImageConstant;

puyoBoard::puyoBoard() : board_r(13), board_c(6), puyoObjectSignal()
{
    board = vector<vector<puyoType>>(board_r, vector<puyoType>(board_c, puyoType::blank));
}

pair<float, float> puyoBoard::get_puyo_spawn_pos() {return make_pair(puyo_spawn_x, puyo_spawn_y);}
void puyoBoard::set_puyo_spawn_pos(float x, float y)
{
    puyo_spawn_x = x;
    puyo_spawn_y = y;
};

pair<int, int> puyoBoard::get_board_size() {return make_pair(board_r, board_c);}
bool puyoBoard::is_in_row(int r) { return 0 <= r && r < board_r; }
bool puyoBoard::is_in_col(int c) { return 0 <= c && c < board_c; }
bool puyoBoard::is_in_board(int r, int c) {return is_in_row(r) && is_in_col(c);} // 이건 행,열

puyoType puyoBoard::get_puyo(int r, int c) {return board[r][c];} // 이건 행,열
void puyoBoard::insert_puyo(puyoType puyo, int r, int c) {board[r][c] = puyo;} // 이건 행,열
void puyoBoard::remove_puyo(int r, int c) {board[r][c] = puyoType::blank;} // 이건 행,열


bool puyoBoard::is_empty()
{
    for (const auto puyo : board.back())
        if (puyo != puyoType::blank)
            return false;
    return true;
}
bool puyoBoard::is_all_cleared() {
    if(!is_empty())
        return false;
    set_signal(puyoBoardSignal::all_cleared);
    return true;
}

puyoBoardEnergyControll& puyoBoard::controll_energy(){return energy_controll;}
puyoBoardGravityControll& puyoBoard::controll_gravity(){return gravity_controll;}
puyoBoardScoreControll& puyoBoard::controll_score(){return score_controll;}
puyoBoardObstructControll& puyoBoard::controll_obstuct(){return obstuct_controll;}
puyoBoardVanishControll& puyoBoard::controll_vanish(){return vanish_controll;}
puyoBoardFutureControll& puyoBoard::controll_future(){return future_controll;}



