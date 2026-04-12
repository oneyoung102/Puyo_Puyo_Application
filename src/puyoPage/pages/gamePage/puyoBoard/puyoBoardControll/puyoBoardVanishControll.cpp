#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoBoardControll/puyoBoardVanishControll.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoPuyo/puyoAction/puyoPuyoVanish.hpp"
#include <queue>
#include <utility>

using namespace std;

puyoBoardVanishControll::puyoBoardVanishControll()
    : dir({{1, 0}, {-1, 0}, {0, 1}, {0, -1}})
{}

void puyoBoardVanishControll::add(PUYO_INFO puyo)
{
    vanish_puyos.push_back(
        puyoPuyo(std::get<0>(puyo),std::get<1>(puyo),std::get<2>(puyo),
        make_unique<puyoPuyoVanish>(std::get<3>(puyo))));
    vanish_puyos.back().let();
}


const vector<puyoPuyo> &puyoBoardVanishControll::get() const { return vanish_puyos; }
bool puyoBoardVanishControll::empty() const { return vanish_puyos.empty(); }

void puyoBoardVanishControll::vanish(puyoBoard& board)
{
    for (int i = 0; i < vanish_puyos.size();)
        if(!vanish_puyos[i].acting())
        {
            std::swap(vanish_puyos[i], vanish_puyos.back());
            vanish_puyos.pop_back();
            board.set_signal(puyoBoardSignal::vanished);
        }
        else
        {
            vanish_puyos[i].act_let(board);
            ++i;
        }
}

void puyoBoardVanishControll::to_vanish_puyo(puyoBoard& board, PUYO_INFO puyo)
{
    const auto[x,y,type,tick] = puyo;
    add({x, y, type, tick});
    board.controll_energy().add_temp({x, y, type, puyoGameConstant::BOARD_FLY_TICK});
    board.remove_puyo(y, x);
}
void puyoBoardVanishControll::find(puyoBoard& board)
{
    const auto[board_r, board_c] = board.get_size();
    vector<vector<bool>> visited(board_r, vector<bool>(board_c, false));
    for (int i = 0; i < board_r; ++i)
        for (int j = 0; j < board_c; ++j)
        {
            if(visited[i][j])
                continue;
            const puyoType puyo = board.get_puyo(i,j);
            if(puyo < puyoType::red || puyoType::pupple < puyo)
                continue;

            int other_puyos = 0;
            vector<tuple<int, int, puyoType>> stored_puyos;
            queue<pair<int, int>> coords;
            coords.push(make_pair(i, j));
            while(!coords.empty())
            {
                const auto [r, c] = coords.front();
                coords.pop();
                if(visited[r][c])
                    continue;
                visited[r][c] = true;

                const puyoType curr_puyo = board.get_puyo(r, c);
                stored_puyos.push_back(make_tuple(r, c, curr_puyo));
                
                if(curr_puyo == puyoType::obstruct)
                {
                    ++other_puyos;
                    continue;
                }
                for (const auto [dr, dc] : dir)
                {
                    const int nr = r + dr, nc = c + dc;
                    if (!board.in(nr, nc))
                        continue;
                    const puyoType npuyo = board.get_puyo(nr, nc);
                    if ((npuyo == puyo || npuyo == puyoType::obstruct) && !visited[nr][nc])
                        coords.push(make_pair(nr, nc));
                }
            }
            const int color_puyo_count = stored_puyos.size() - other_puyos;
            if(color_puyo_count >= condition_for_vanish)
            {
                auto& cs = board.controll_score();
                cs.add_puyo_count(color_puyo_count);
                cs.add_link_count(color_puyo_count);
                cs.add_color_count(puyo); // 방해 뿌요는 종류에 포함 안 시킴

                for(const auto [r, c, type] : stored_puyos)
                {
                    const int tick = (type == puyoType::obstruct) ? puyoGameConstant::BOARD_OBSTRUCT_VANISH_TICK : puyoGameConstant::BOARD_BASIC_VANISH_TICK;
                    to_vanish_puyo(board,{c,r,type,tick});
                }
            }
    }
}
void puyoBoardVanishControll::set_condition(int amount){condition_for_vanish = amount;}
int puyoBoardVanishControll::get_condition() const { return condition_for_vanish; }