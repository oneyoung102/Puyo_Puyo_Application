#include <vector>

#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"

using namespace std;

puyoBoard::puyoBoard() : size({6,13}), puyoObjectSignal()
{
    board = vector<vector<puyoType>>(size.r, vector<puyoType>(size.c, puyoType::blank));
}

POSf puyoBoard::get_spawn_pos() const {return spawn_pos;}
void puyoBoard::set_spawn_pos(POSf pos){spawn_pos = pos;};

POSi puyoBoard::get_size() const {return size;}
bool puyoBoard::in_row(int r) const { return 0 <= r && r < size.r; }
bool puyoBoard::in_col(int c) const { return 0 <= c && c < size.c; }
bool puyoBoard::in(POSi pos) const {return in_row(pos.r) && in_col(pos.c);} // 이건 행,열
bool puyoBoard::touched(POSi pos) const// 이건 행,열
{
    return pos.r >= 0 && (!in(pos) || !empty(pos))
        || pos.r < 0 && !in_col(pos.c);
}

puyoType puyoBoard::get_puyo(POSi pos) const {return board[pos.r][pos.c];} // 이건 행,열
void puyoBoard::insert_puyo(puyoType puyo, POSi pos) {board[pos.r][pos.c] = puyo;} // 이건 행,열
void puyoBoard::remove_puyo(POSi pos) {board[pos.r][pos.c] = puyoType::blank;} // 이건 행,열

bool puyoBoard::empty() const
{
    for (const auto puyo : board.back())
        if (puyo != puyoType::blank)
            return false;
    return true;
}
bool puyoBoard::empty(POSi pos) const {return get_puyo(pos) == puyoType::blank;}
bool puyoBoard::all_cleared(){
    if(!empty())
        return false;
    set_signal(puyoBoardSignal::all_cleared);
    return true;
}

vector<PUYO_INFO> puyoBoard::to_gravity_puyo()
{
    vector<PUYO_INFO> gravity_puyos;
    for(int j = 0 ; j < size.c; ++j)
    {
        bool floating = false;
        for(int i = size.r-1 ; i >= 0 ; --i)
        {
            const auto pos = POSi(j,i);
            if(empty(pos))
                floating = true;
            else if(floating)
            {
                gravity_puyos.push_back({pos, get_puyo(pos), puyoGameConstant::BOARD_FALL_GRAVITY_TICK});
                remove_puyo(pos);
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



