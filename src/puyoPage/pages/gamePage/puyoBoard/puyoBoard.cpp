#include <vector>

#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/puyoType.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"

using namespace std;

puyoBoard::puyoBoard()
    : size(puyoGameConstant::BOARD_BASIC_SIZE)
    , puyoObjectSignal()
{
    board = vector<vector<puyoType>>(size.r, vector<puyoType>(size.c, puyoType()));
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

puyoType puyoBoard::get_puyo(POSs pos) const {return board[pos.r][pos.c];} // 이건 행,열
void puyoBoard::insert_puyo(puyoType puyo, POSs pos) {board[pos.r][pos.c] = puyo;} // 이건 행,열
void puyoBoard::remove_puyo(POSs pos) {board[pos.r][pos.c] = puyoType();} // 이건 행,열

bool puyoBoard::empty() const
{
    for (const auto& puyo : board.back())
        if(puyo.empty())
            return false;
    return true;
}
bool puyoBoard::empty(POSs pos) const {return board[pos.r][pos.c].empty();}
bool puyoBoard::all_cleared(){
    if(!empty())
        return false;
    set_signal(puyoBoardSignal::all_cleared);
    return true;
}

vector<PUYO_INFO> puyoBoard::to_gravity_puyo()
{
    vector<PUYO_INFO> gravity_puyos;
    for(size_t j = 0 ; j < size.c; ++j)
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

const puyoBoardEnergyControll& puyoBoard::controll_energy() const {return energy_controll;}
const puyoBoardGravityControll& puyoBoard::controll_gravity() const {return gravity_controll;}
const puyoBoardScoreControll& puyoBoard::controll_score() const {return score_controll;}
const puyoBoardObstructControll& puyoBoard::controll_obstuct() const {return obstuct_controll;}
const puyoBoardVanishControll& puyoBoard::controll_vanish() const {return vanish_controll;}
const puyoBoardFutureControll& puyoBoard::controll_future() const {return future_controll;}



