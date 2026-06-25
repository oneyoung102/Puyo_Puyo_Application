#include <vector>

#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoAction/puyoPuyoGravity.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoAction/puyoPuyoVanish.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoType/puyoType.hpp"
#include "puyoTool/puyoCast.hpp"

using namespace std;

puyoBoard::puyoBoard()
    : size(puyoGameConstant::BOARD_BASIC_SIZE)
    , puyoObjectSignal()
{
    board = vector<vector<puyoPuyo>>(size.r, vector<puyoPuyo>(size.c, puyoPuyo()));
    for (int r = 0; r < size.r; ++r)
        for (int c = 0; c < size.c; ++c)
            board[r][c].move(POSs(c, r));
}

POSf puyoBoard::get_spawn_pos() const { return spawn_pos; }
void puyoBoard::set_spawn_pos(const POSf &pos) { spawn_pos = pos; };
bool puyoBoard::spawn_able() const { return empty(spawn_pos); }

POSi puyoBoard::get_size() const { return size; }
bool puyoBoard::in_row(int r) const { return 0 <= r && r < size.r; }
bool puyoBoard::in_col(int c) const { return 0 <= c && c < size.c; }
bool puyoBoard::in(const POSi& pos) const {return in_row(pos.r) && in_col(pos.c);}
bool puyoBoard::touched(const POSi& pos) const
{
    return pos.r >= 0 && (!in(pos) || !empty(pos))
        || pos.r < 0 && !in_col(pos.c);
}

const puyoPuyo& puyoBoard::view(const POSs& pos) const {return board.at(pos.r).at(pos.c);}
puyoPuyo& puyoBoard::refer(const POSs& pos){ return board.at(pos.r).at(pos.c); }
//puyoPuyo& puyoBoard::operator[](const POSs& pos) { return board.at(pos.r).at(pos.c); }

void puyoBoard::insert(const puyoPuyo& puyo, const POSs& pos)
{
    board.at(pos.r).at(pos.c) = puyo;
    board.at(pos.r).at(pos.c).move(pos);
}
void puyoBoard::insert(const puyoPuyo& puyo)
{
    const auto [c, r] = puyo.get_pos();
    board.at(CASTs(r)).at(CASTs(c)) = puyo;
}
void puyoBoard::insert(puyoPuyo&& puyo, const POSs& pos)
{
    board.at(pos.r).at(pos.c) = std::move(puyo);
    board.at(pos.r).at(pos.c).move(pos);
}
void puyoBoard::insert(puyoPuyo&& puyo)
{
    const auto [c, r] = puyo.get_pos();
    board.at(CASTs(r)).at(CASTs(c)) = std::move(puyo);
}

void puyoBoard::remove(const POSs& pos){board.at(pos.r).at(pos.c) = puyoPuyo(pos);}

bool puyoBoard::empty(const POSs& pos) const {return board.at(pos.r).at(pos.c).empty();}
bool puyoBoard::all_cleared()
{
    for(int r = size.r-1 ; r >= 0 ; --r)
        for(const auto& puyo : board[r])
            if(!puyo.empty() && !puyo.is_same(puyoType::Type::bomb) && puyo.is_gravityable())
                return false;
    signal(puyoBoardSignal::all_cleared);
    return true;
}

vector<puyoPuyo> puyoBoard::to_gravity_puyo()
{
    vector<puyoPuyo> gravity_puyos;
    for(size_t j = 0; j < size.c; ++j)
    {
        bool floating = false;
        for(int i = size.r - 1; i >= 0; --i)
        {
            const auto& pos = POSi(j, i);
            auto& puyo = refer(pos);
            if(empty(pos))
                floating = true;
            else if(!puyo.is_gravityable())
                floating = false;
            else if(floating)
            {
                puyo.set_act(make_unique<puyoPuyoGravity>(puyoGameConstant::BOARD_FALL_GRAVITY_TICK));
                gravity_puyos.push_back(std::move(puyo));
                remove(pos);
                continue;
            }
        }
    }
    return gravity_puyos;
}
puyoPuyo puyoBoard::to_vanish_puyo(const POSs& pos)
{
    auto& puyo = refer(pos);
    const int tick = puyo.is_colored() ? puyoGameConstant::BOARD_COLOR_VANISH_TICK : puyoGameConstant::BOARD_OTHER_VANISH_TICK;

    if(puyo.is_frozen())
    {
        auto vanish_puyo = puyo;
        vanish_puyo.set_act(make_unique<puyoPuyoVanish>(tick));
        puyo.unfreeze();
        signal(puyoBoardSignal::unfreeze);
        return vanish_puyo;
    }
    else
    {
        auto vanish_puyo = std::move(puyo);
        remove(pos);
        vanish_puyo.set_act(make_unique<puyoPuyoVanish>(tick));
        return vanish_puyo;
    }
}

vector<pair<puyoType::State,POSs>> puyoBoard::update()
{
    vector<pair<puyoType::State,POSs>> states;
    for(size_t c = 0; c < size.c; ++c)
        for(int r = size.r - 1; r >= 0; --r)
        {
            auto pos = POSs(c, r);
            auto& puyo = refer(pos);
            if(puyo.empty())
                break;
            puyo.update();
            if(puyo.get_type_state() == puyoType::State::none)
                continue;
            states.push_back({puyo.get_type_state(),std::move(pos)});
        }
    return states;
}
