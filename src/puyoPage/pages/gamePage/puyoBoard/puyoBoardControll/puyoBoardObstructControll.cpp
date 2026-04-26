#include "puyoPage/pages/gamePage/puyoBoard/puyoBoardControll/puyoBoardObstructControll.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"

#include <utility>

using namespace std;
using namespace puyoGameConstant;

puyoBoardObstructControll::puyoBoardObstructControll()
{
    obstruct_puyo = 0;
    opposite_obstruct_puyo = 0;
    approvement_spawn = false;
}

void puyoBoardObstructControll::add(int count)
{
    obstruct_puyo = min(max(0, obstruct_puyo + count), OBSTRUCT_PUYO_VIEWER_UNIT.back() * 6);
}
std::vector<PUYO_INFO> puyoBoardObstructControll::to_gravity_puyo(puyoBoard& board, int obstruct_puyo_for_dropping)
{
    if(obstruct_puyo_for_dropping <= 0)
        return {};

    if(obstruct_puyo_for_dropping >= OBSTRUCT_PUYO_MANY)
        board.set_signal(puyoBoardSignal::many_obsp_dropped);
    else if(obstruct_puyo_for_dropping >= OBSTRUCT_PUYO_MID)
        board.set_signal(puyoBoardSignal::mid_obsp_dropped);
    else
        board.set_signal(puyoBoardSignal::less_obsp_dropped);
    
    const auto[board_r, board_c] = board.get_size();
    vector<int> obstruct_puyo_height(board_c, 0);
    vector<PUYO_INFO> gravity_puyos;
    for(int i = board_r-1; i >= 0 ; --i)
        for(int j = 0; j < board_c ; ++j)
            if(board.empty(i,j))
            {
                gravity_puyos.push_back({{(float)j,-obstruct_puyo_height[j] + OBSTRUCT_PUYO_SPAWN_Y}, puyoType::obstruct, BOARD_FALL_GRAVITY_TICK});
                ++obstruct_puyo_height[j];
                --obstruct_puyo_for_dropping;
                --obstruct_puyo;
                if(obstruct_puyo_for_dropping <= 0)
                    return std::move(gravity_puyos);
            }
    return {};
}
bool puyoBoardObstructControll::empty() const { return obstruct_puyo == 0; }
const int &puyoBoardObstructControll::get() const { return obstruct_puyo; }

void puyoBoardObstructControll::add_opp(int count){opposite_obstruct_puyo += count;}
int puyoBoardObstructControll::get_opp() const {return opposite_obstruct_puyo;}
bool puyoBoardObstructControll::empty_opp() const { return opposite_obstruct_puyo == 0;}
void puyoBoardObstructControll::clear_opp(){opposite_obstruct_puyo = 0;}

void puyoBoardObstructControll::approve_spawn() {approvement_spawn = true;}
void puyoBoardObstructControll::disapprove_spawn() {approvement_spawn = false;}
bool puyoBoardObstructControll::spawn_approved() const  {return approvement_spawn;}