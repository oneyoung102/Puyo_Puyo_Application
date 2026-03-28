#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include "puyoPage/pages/gamePage/puyoTempPuyo/puyoVanishPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoBoardControll/puyoBoardVanishControll.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include <queue>
#include <utility>

using namespace std;

puyoBoardVanishControll::puyoBoardVanishControll()
    : dir({{1, 0}, {-1, 0}, {0, 1}, {0, -1}})
{}

void puyoBoardVanishControll::push_vanish_puyo(puyoVanishPuyo &&ptp){vanish_puyos.push_back(std::move(ptp));}


vector<puyoVanishPuyo> &puyoBoardVanishControll::get_vanish_puyos() { return vanish_puyos; }
bool puyoBoardVanishControll::vanish_puyo_empty() { return vanish_puyos.empty(); }

void puyoBoardVanishControll::vanish_vanish_puyos(puyoBoard& board)
{
    for (int i = 0; i < vanish_puyos.size();)
    {
        if (vanish_puyos[i].vanish_stopped())
        {
            std::swap(vanish_puyos[i], vanish_puyos.back());
            const auto [x, y] = vanish_puyos.back().get_puyo_pos();
            const auto color = vanish_puyos.back().get_puyo_color();
            board
            .controll_energy()
            .add_temp_energy_puyo(make_tuple(x, y, color));

            vanish_puyos.pop_back();
            board.set_signal(puyoBoardSignal::vanished);
        }
        else
        {
            vanish_puyos[i].vanish_let(board);
            ++i;
        }
    }
}

void puyoBoardVanishControll::vanish_deployed_puyo(puyoBoard& board, int x, int y, puyoType type, int tick)
{
    push_vanish_puyo(std::move(puyoVanishPuyo(x, y, type, tick)));
    board.remove_puyo(y, x);
}
void puyoBoardVanishControll::find_vanish_puyo(puyoBoard& board)
{
    const auto[board_r, board_c] = board.get_board_size();
    vector<vector<bool>> visited(board_r, vector<bool>(board_c, false));
    for (int i = 0; i < board_r; ++i)
        for (int j = 0; j < board_c; ++j)
        {
            puyoType puyo = board.get_puyo(i,j);
            if (puyo == puyoType::blank || puyo == puyoType::obstruct || visited[i][j])
                continue;
            int obstruct_puyo_counting = 0;
            vector<tuple<int, int, puyoType>> stored_puyos;
            queue<pair<int, int>> coords;
            coords.push(make_pair(i, j));
            while(!coords.empty())
            {
                const auto [r, c] = coords.front();
                coords.pop();
                if(visited[r][c])
                    continue;

                puyoType curr_puyo = board.get_puyo(r, c);
                stored_puyos.push_back(make_tuple(r, c, curr_puyo));
                visited[r][c] = true;

                if (curr_puyo == puyoType::obstruct)
                {
                    ++obstruct_puyo_counting;
                    continue;
                }
                for (const auto [dr, dc] : dir)
                {
                    int nr = r + dr, nc = c + dc;
                    if (!board.is_in_board(nr, nc))
                        continue;
                    puyoType npuyo = board.get_puyo(nr, nc);
                    if ((npuyo == puyo || npuyo == puyoType::obstruct) && !visited[nr][nc])
                        coords.push(make_pair(nr, nc));
                }
            }
            const int puyo_count_except_obsp = stored_puyos.size() - obstruct_puyo_counting;
            if (puyo_count_except_obsp >= condition_for_vanish)
            {
                auto& cs = board.controll_score();
                cs.add_puyo_count(puyo_count_except_obsp);
                cs.add_link_count(puyo_count_except_obsp);
                cs.add_color_count(puyo); // 방해 뿌요는 종류에 포함 안 시킴

                for (const auto [r, c, type] : stored_puyos)
                {
                    const int tick = (type == puyoType::obstruct) ? puyoGameConstant::BOARD_OBSTRUCT_VANISH_TICK : puyoGameConstant::BOARD_BASIC_VANISH_TICK;
                    vanish_deployed_puyo(board,c,r,type,tick);
                }
            }
    }
}
void puyoBoardVanishControll::set_condition_for_vanish(int amount){condition_for_vanish = amount;}
int puyoBoardVanishControll::get_condition_for_vanish() { return condition_for_vanish; }