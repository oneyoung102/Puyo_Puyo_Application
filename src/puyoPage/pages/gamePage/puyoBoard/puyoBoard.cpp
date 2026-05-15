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
bool puyoBoard::spawn_able() const {return empty(spawn_pos);}

POSi puyoBoard::get_size() const {return size;}
bool puyoBoard::in_row(int r) const { return 0 <= r && r < size.r; }
bool puyoBoard::in_col(int c) const { return 0 <= c && c < size.c; }
bool puyoBoard::in(POSi pos) const {return in_row(pos.r) && in_col(pos.c);}
bool puyoBoard::touched(POSi pos) const
{
    return pos.r >= 0 && (!in(pos) || !empty(pos))
        || pos.r < 0 && !in_col(pos.c);
}

puyoType puyoBoard::get_puyo(POSs pos) const {return board[pos.r][pos.c];}
puyoType& puyoBoard::ref_puyo(POSs pos) {return board[pos.r][pos.c];}
void puyoBoard::insert_puyo(puyoType puyo, POSs pos) {board[pos.r][pos.c] = puyo;}
void puyoBoard::remove_puyo(POSs pos) {board[pos.r][pos.c] = puyoType();}

bool puyoBoard::empty() const
{
    for (const auto& puyo : board.back())
        if(!puyo.empty())
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
                gravity_puyos.push_back({pos, ref_puyo(pos), puyoGameConstant::BOARD_FALL_GRAVITY_TICK});
                remove_puyo(pos);
                continue;
            }
        }
    }
    return std::move(gravity_puyos);
}
vector<_puyoType::typeState> puyoBoard::update()
{
    vector<_puyoType::typeState> states;
    for(size_t c = 0 ; c < size.c ; ++c)
        for(int r = size.r-1 ; r >= 0 ; --r)
        {
            auto& puyo = ref_puyo(POSs(c,r));
            if(puyo.empty())
                break;
            puyo.update();
            if(puyo.get_state() == _puyoType::typeState::none)
                continue;
            states.push_back(puyo.get_state());
        }
    return std::move(states);
}




