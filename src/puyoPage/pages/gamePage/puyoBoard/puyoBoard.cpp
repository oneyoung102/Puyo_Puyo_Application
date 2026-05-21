#include <cmath>
#include <stdexcept>
#include <vector>

#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoAction/puyoPuyoGravity.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/puyoType.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"

using namespace std;

puyoBoard::puyoBoard()
    : size(puyoGameConstant::BOARD_BASIC_SIZE)
    , puyoObjectSignal()
{
    board = vector<vector<puyoPuyo>>(size.r, vector<puyoPuyo>(size.c, puyoPuyo()));
}

POSf puyoBoard::get_spawn_pos() const {return spawn_pos;}
void puyoBoard::set_spawn_pos(const POSf& pos){spawn_pos = pos;};
bool puyoBoard::spawn_able() const {return empty(spawn_pos);}

POSi puyoBoard::get_size() const {return size;}
bool puyoBoard::in_row(int r) const { return 0 <= r && r < size.r; }
bool puyoBoard::in_col(int c) const { return 0 <= c && c < size.c; }
bool puyoBoard::in(const POSi& pos) const {return in_row(pos.r) && in_col(pos.c);}
bool puyoBoard::touched(const POSi& pos) const
{
    return pos.r >= 0 && (!in(pos) || !empty(pos))
        || pos.r < 0 && !in_col(pos.c);
}

const puyoPuyo& puyoBoard::get_puyo(const POSs& pos) const {return board[pos.r][pos.c];}
puyoPuyo& puyoBoard::ref_puyo(const POSs& pos) {return board[pos.r][pos.c];}
void puyoBoard::insert_puyo(const puyoPuyo& puyo, const POSs& pos)
{
    board[pos.r][pos.c] = puyo;
    board[pos.r][pos.c].move(pos);
}
void puyoBoard::insert_puyo(const puyoPuyo& puyo)
{
    const auto[c,r] = puyo.get_pos();
    if(!in_row(r) || !in_col(c))
        throw runtime_error("When inserting puyo, out of board");
    board[CASTs(r)][CASTs(c)] = std::move(puyo);
}
void puyoBoard::remove_puyo(const POSs& pos) {board[pos.r][pos.c] = puyoPuyo();}

bool puyoBoard::empty() const
{
    for (const auto& puyo : board.back())
        if(!puyo.empty())
            return false;
    return true;
}
bool puyoBoard::empty(const POSs& pos) const {return board[pos.r][pos.c].empty();}
bool puyoBoard::all_cleared(){
    if(!empty())
        return false;
    set_signal(puyoBoardSignal::all_cleared);
    return true;
}

vector<puyoPuyo> puyoBoard::to_gravity_puyo()
{
    vector<puyoPuyo> gravity_puyos;
    for(size_t j = 0 ; j < size.c; ++j)
    {
        bool floating = false;
        for(int i = size.r-1 ; i >= 0 ; --i)
        {
            const auto& pos = POSi(j,i);
            if(empty(pos))
                floating = true;
            else if(floating)
            {
                ref_puyo(pos).set_act(make_unique<puyoPuyoGravity>(puyoGameConstant::BOARD_FALL_GRAVITY_TICK));
                gravity_puyos.push_back(std::move(ref_puyo(pos)));
                remove_puyo(pos);
                continue;
            }
        }
    }
    return gravity_puyos;
}
vector<puyoType::typeState> puyoBoard::update()
{
    vector<puyoType::typeState> states;
    for(size_t c = 0 ; c < size.c ; ++c)
        for(int r = size.r-1 ; r >= 0 ; --r)
        {
            auto& puyo = ref_puyo(POSs(c,r));
            if(puyo.empty())
                break;
            puyo.update();
            if(puyo.get_type_state() == puyoType::typeState::none)
                continue;
            states.push_back(puyo.get_type_state());
        }
    return states;
}




