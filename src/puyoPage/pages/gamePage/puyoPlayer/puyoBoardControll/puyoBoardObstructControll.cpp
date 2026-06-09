#include "puyoPage/pages/gamePage/puyoPlayer/puyoBoardControll/puyoBoardObstructControll.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoAction/puyoPuyoGravity.hpp"

using namespace std;
using namespace puyoGameConstant;

puyoBoardObstructControll::puyoBoardObstructControll()
    : obstruct_puyo(0)
    , opposite_obstruct_puyo(0)
    , approvement_spawn(false)
{}

void puyoBoardObstructControll::add(int count)
{
    obstruct_puyo = min(max(0, obstruct_puyo + count), OBSTRUCT_VIEWER_UNIT.back() * OBSTRUCT_VIEWER_UPPER);
}
std::vector<puyoPuyo> puyoBoardObstructControll::to_gravity_puyo(puyoBoard& board, int obstruct_puyo_for_dropping)
{
    if(obstruct_puyo_for_dropping <= 0)
        return {};
    if(obstruct_puyo_for_dropping >= OBSTRUCT_PUYO_MANY)
        board.set_signal(puyoBoardSignal::many_obsp_dropped);
    else if(obstruct_puyo_for_dropping >= OBSTRUCT_PUYO_MID)
        board.set_signal(puyoBoardSignal::mid_obsp_dropped);
    else
        board.set_signal(puyoBoardSignal::less_obsp_dropped);
    
    const auto bsize = board.get_size();
    vector<int> obstruct_puyo_height(bsize.c, 0), floor_height(bsize.c,bsize.r);
    for(size_t c = 0; c < bsize.c ; ++c)
        for(size_t r = 0 ; r < bsize.r ; ++r)
        {
            const auto& puyo = board.get_puyo({c,r});
            if(!puyo.empty() && !puyo.is_gravityable())
            {
                floor_height[c] = r;
                break;
            }
        }
    vector<puyoPuyo> gravity_puyos;
    for(int r = bsize.r-1; ; --r)
        for(size_t c = 0; c < bsize.c ; ++c)
            if(!board.in_row(r) || board.empty(POSi(c, r)) && r < floor_height[c])
            {
                gravity_puyos.push_back(puyoPuyo(POSf(c,-obstruct_puyo_height[c]+OBSTRUCT_PUYO_SPAWN_Y), P_OBSTRUCT, make_unique<puyoPuyoGravity>(BOARD_FALL_GRAVITY_TICK)));
                ++obstruct_puyo_height[c];
                --obstruct_puyo;
                --obstruct_puyo_for_dropping;
                if(obstruct_puyo_for_dropping <= 0)
                    return gravity_puyos;
            }
    return gravity_puyos;
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