#include "puyoPage/pages/gamePage/puyoBoard/puyoBoardControll/puyoBoardObstructControll.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"

#include <queue>
#include <utility>

using namespace std;
using namespace puyoGameConstant;

puyoBoardObstructControll::puyoBoardObstructControll()
{
    obstruct_puyo = 0;
    approvement_for_obstruct_puyo = false;
    temp_obstruct_puyo = 0;
}

void puyoBoardObstructControll::give(int count)
{
     obstruct_puyo = min(max(0, obstruct_puyo + count), ::OBSTRUCT_PUYO_VIEWER_UNIT.back() * 6);
}
void puyoBoardObstructControll::spawn(puyoBoard& board, int obstruct_puyo_for_dropping)
{
    if (!approvement_for_obstruct_puyo || obstruct_puyo_for_dropping == 0)
        return;
    approvement_for_obstruct_puyo = false;
    const auto[board_r, board_c] = board.get_size();

    board.set_signal(puyoBoardSignal::spawn_obsp);
    temp_obstruct_puyo = obstruct_puyo_for_dropping;
    vector<int> obstruct_puyo_height(board_c, 0);
    priority_queue<pair<int, int>, vector<pair<int, int>>,greater<pair<int, int>>> pq; // {height,col}
    for (int i = 0; i < board_c; ++i)
        for (int j = 0; j <= board_r; ++j)
            if (j == board_r || board.get_puyo(j,i) != puyoType::blank)
            {
                pq.push(make_pair(board_r - j, i));
                break;
            }
    while (obstruct_puyo_for_dropping > 0)
    {
        auto [height, col] = pq.top();
        pq.pop();
        --obstruct_puyo_for_dropping;
        --obstruct_puyo;
        board.controll_gravity()
        .add({col, -obstruct_puyo_height[col] + OBSTRUCT_PUYO_SPAWN_Y, puyoType::obstruct, BOARD_FALL_GRAVITY_TICK});
        ++obstruct_puyo_height[col];
        pq.push(make_pair(height + 1, col));
    }
}
bool puyoBoardObstructControll::empty() const { return obstruct_puyo == 0; }
const int &puyoBoardObstructControll::get() const { return obstruct_puyo; }


int puyoBoardObstructControll::temp_get() {return exchange(temp_obstruct_puyo, 0);}
void puyoBoardObstructControll::approve_spawn() {approvement_for_obstruct_puyo = true;}
void puyoBoardObstructControll::disapprove_spawn() {approvement_for_obstruct_puyo = false;}