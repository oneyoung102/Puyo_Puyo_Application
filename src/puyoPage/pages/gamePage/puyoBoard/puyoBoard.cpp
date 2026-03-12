#include <queue>
#include <tuple>
#include <utility>
#include <vector>

#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoPage/pages/gamePage/puyoGameConstant.hpp"
#include "puyoPage/pages/gamePage/puyoTempPuyo/puyoEnergyPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoTempPuyo/puyoGravityPuyo.hpp"
#include "puyoPage/pages/gamePage/puyoTempPuyo/puyoVanishPuyo.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

using namespace std;
using namespace puyoImageConstant;
using namespace puyoGameConstant;

puyoBoard::puyoBoard() : board_r(13), board_c(6), puyoObjectSignal() {
  dir = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
  obstruct_puyo = 0;

  board = vector<vector<Type>>(board_r, vector<Type>(board_c, Type::blank));
  gravity_puyo_is_out_in_board = false;

  puyo_count = 0;
  chain_count = 0;
  temp_obstruct_puyo = 0;
  approvement_for_obstruct_puyo = false;
}

pair<float, float> puyoBoard::get_puyo_spawn_pos() {
  return make_pair(puyo_spawn_x, puyo_spawn_y);
}
void puyoBoard::set_puyo_spawn_pos(float x, float y) {
  puyo_spawn_x = x;
  puyo_spawn_y = y;
};

pair<int, int> puyoBoard::get_board_size() {
  return make_pair(board_r, board_c);
}
bool puyoBoard::is_in_row(int r) { return 0 <= r && r < board_r; }
bool puyoBoard::is_in_col(int c) { return 0 <= c && c < board_c; }
bool puyoBoard::is_in_board(int r, int c) {
  return is_in_row(r) && is_in_col(c);
} // 이건 행,열

puyoBoard::Type puyoBoard::get_puyo(int r, int c) {
  return board[r][c];
} // 이건 행,열
void puyoBoard::insert_puyo(Type puyo, int r, int c) {
  board[r][c] = puyo;
} // 이건 행,열
void puyoBoard::remove_puyo(int r, int c) {
  board[r][c] = Type::blank;
} // 이건 행,열

void puyoBoard::push_gravity_puyo(puyoGravityPuyo &&ptp) // std::move
{
  gravity_puyos.push_back(std::move(ptp));
}
void puyoBoard::push_gravity_puyo(vector<puyoGravityPuyo> &&ptp_v) // std::move
{
  for (auto &&ptp : ptp_v)
    push_gravity_puyo(std::move(ptp));
}
void puyoBoard::push_vanish_puyo(puyoVanishPuyo &&ptp) // std::move
{
  vanish_puyos.push_back(std::move(ptp));
}

vector<puyoGravityPuyo> &puyoBoard::get_gravity_puyos() {
  return gravity_puyos;
}
vector<puyoVanishPuyo> &puyoBoard::get_vanish_puyos() { return vanish_puyos; }
vector<puyoFuturePuyo> &puyoBoard::get_future_puyos() { return future_puyos; }
vector<puyoEnergyPuyo> &puyoBoard::get_energy_puyos() { return energy_puyos; }
bool puyoBoard::gravity_puyo_empty() { return gravity_puyos.empty(); }
bool puyoBoard::vanish_puyo_empty() { return vanish_puyos.empty(); }
bool puyoBoard::temp_energy_puyo_empty() {
  return temp_energy_puyos.empty();
}
bool puyoBoard::gravity_puyo_is_out() { return gravity_puyo_is_out_in_board; }

void puyoBoard::gravity_gravity_puyos() {
  for (int i = 0; i < gravity_puyos.size();) {
    if (gravity_puyos[i].gravity_stopped()) {
      if (!gravity_puyos[i].deploy_puyo(*this))
        gravity_puyo_is_out_in_board = true; // 배치할 뿌요가 범위를 나감
      std::swap(gravity_puyos[i], gravity_puyos.back());
      gravity_puyos.pop_back();
    } else {
      gravity_puyos[i].gravity_let(*this);
      ++i;
    }
  }
}
void puyoBoard::vanish_vanish_puyos() {
  for (int i = 0; i < vanish_puyos.size();) {
    if (vanish_puyos[i].vanish_stopped()) {
      std::swap(vanish_puyos[i], vanish_puyos.back());

      auto [x, y] = vanish_puyos.back().get_puyo_pos();
      int color = vanish_puyos.back().get_puyo_color();
      temp_energy_puyos.push_back(make_tuple(x, y, color));

      vanish_puyos.pop_back();
      signals[(int)puyoBoardSignal::vanished] = true;
    } else {
      vanish_puyos[i].vanish_let(*this);
      ++i;
    }
  }
}
void puyoBoard::fly_energy_puyos() {
  for (int i = 0; i < energy_puyos.size();) {
    if (energy_puyos[i].fly_stopped()) {
      std::swap(energy_puyos[i], energy_puyos.back());
      energy_puyos.pop_back();
    } else {
      energy_puyos[i].fly_let(*this);
      ++i;
    }
  }
}

int puyoBoard::get_chain_count() { return chain_count; }
void puyoBoard::add_chain_count() {
  signals[(int)puyoBoardSignal::chain] = true;
  ++chain_count;
}
void puyoBoard::reset_chain_count() { chain_count = 0; }
int puyoBoard::get_puyo_count() { return exchange(puyo_count, 0); }
vector<int> puyoBoard::get_link_count() {
  vector<int> temp = link_count;
  link_count.clear();
  return temp;
}
int puyoBoard::get_color_count() {
  int temp = color_count.size();
  color_count.clear();
  return temp;
}

void puyoBoard::find_gravity_puyo() {
  for (int i = 0; i < board_c; ++i) {
    bool push = false;
    for (int j = board_r - 1; j >= 0; --j) // 아래에 있는 뿌요가 먼저 오게
    {
      Type puyo = board[j][i];
      if (puyo != Type::blank) {
        if (push) {
          push_gravity_puyo(std::move(
              puyoGravityPuyo(i, j, (int)puyo, BOARD_FALL_GRAVITY_TICK)));
          remove_puyo(j, i);
          continue;
        }
      } else
        push = true;
    }
  }
}

void puyoBoard::find_vanish_puyo() {
  vector<vector<bool>> visited(board_r, vector<bool>(board_c, false));
  for (int i = 0; i < board_r; ++i)
    for (int j = 0; j < board_c; ++j) {
      Type puyo = board[i][j];
      if (puyo == Type::blank || puyo == Type::obstruct || visited[i][j])
        continue;
      int obstruct_puyo_counting = 0;
      vector<tuple<int, int, Type>> stored_puyos;
      queue<pair<int, int>> coords;
      coords.push(make_pair(i, j));
      while (!coords.empty()) {
        auto [r, c] = coords.front();
        coords.pop();
        if (visited[r][c])
          continue;

        Type curr_puyo = get_puyo(r, c);
        stored_puyos.push_back(make_tuple(r, c, curr_puyo));
        visited[r][c] = true;

        if (curr_puyo == Type::obstruct) {
          ++obstruct_puyo_counting;
          continue;
        }
        for (const auto [dr, dc] : dir) {
          int nr = r + dr, nc = c + dc;
          if (!is_in_board(nr, nc))
            continue;
          Type npuyo = get_puyo(nr, nc);
          if ((npuyo == puyo || npuyo == Type::obstruct) && !visited[nr][nc])
            coords.push(make_pair(nr, nc));
        }
      }
      int puyo_count_except_obsp = stored_puyos.size() - obstruct_puyo_counting;
      if (puyo_count_except_obsp >= condition_for_vanish) {
        puyo_count += puyo_count_except_obsp;
        link_count.push_back(puyo_count_except_obsp);
        color_count.insert(puyo); // 방해 뿌요는 종류에 포함 안 시킴

        for (const auto [r, c, type] : stored_puyos) {
          if (type == Type::obstruct)
            push_vanish_puyo(std::move(
                puyoVanishPuyo(c, r, (int)type, BOARD_OBSTRUCT_VANISH_TICK)));
          else
            push_vanish_puyo(std::move(
                puyoVanishPuyo(c, r, (int)type, BOARD_BASIC_VANISH_TICK)));
          remove_puyo(r, c);
        }
      }
    }
}
void puyoBoard::find_future_puyos(puyoPlayPuyo &puyo) {
  future_puyos.clear();
  auto [x1, y1, x2, y2] = puyo.get_puyo_pos();
  auto [color1, color2] = puyo.get_puyo_color();
  for (int y = (int)y1; y < board_r; ++y)
    if (puyo.puyo_touched(*this, round(x1), y + 1)) {
      if (y1 < y2)
        --y; // 실제로 뿌요를 배치하지 않기에 보정
      future_puyos.push_back(puyoFuturePuyo(round(x1), y, color1));
      break;
    }
  for (int y = (int)y2; y < board_r; ++y)
    if (puyo.puyo_touched(*this, round(x2), y + 1)) {
      if (y1 > y2)
        --y; // 실제로 뿌요를 배치하지 않기에 보정
      future_puyos.push_back(puyoFuturePuyo(round(x2), y, color2));
      break;
    }
}
void puyoBoard::remove_future_puyos() { future_puyos.clear(); }

void puyoBoard::give_obstruct_puyo(int count) {
  obstruct_puyo =
      min(max(0, obstruct_puyo + count), OBSTRUCT_PUYO_VIEWER_UNIT.back() * 6);
}
void puyoBoard::spawn_obstruct_puyo(int obstruct_puyo_for_dropping) {
  if (!approvement_for_obstruct_puyo || obstruct_puyo_for_dropping == 0)
    return;
  approvement_for_obstruct_puyo = false;

  signals[(int)puyoBoardSignal::spawn_obsp] = true;
  temp_obstruct_puyo = obstruct_puyo_for_dropping;
  vector<int> obstruct_puyo_height(board_c, 0);
  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      pq; // {height,col}
  for (int i = 0; i < board_c; ++i)
    for (int j = 0; j <= board_r; ++j)
      if (j == board_r || board[j][i] != Type::blank)
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
    gravity_puyos.push_back(
        puyoGravityPuyo(col, -obstruct_puyo_height[col] + OBSTRUCT_PUYO_SPAWN_Y,
                        (int)Type::obstruct, BOARD_FALL_GRAVITY_TICK));
    ++obstruct_puyo_height[col];
    pq.push(make_pair(height + 1, col));
  }
}
bool puyoBoard::obstructed_puyo_empty() { return obstruct_puyo == 0; }
int &puyoBoard::get_obstruct_puyo() { return obstruct_puyo; }

void puyoBoard::set_condition_for_vanish(int amount) {
  condition_for_vanish = amount;
}
int puyoBoard::get_condition_for_vanish() { return condition_for_vanish; }

bool puyoBoard::is_empty() {
  for (const auto puyo : board.back())
    if (puyo != Type::blank)
      return false;
  return true;
}
bool puyoBoard::is_all_cleared() {
  if (is_empty()) {
    signals[(int)puyoBoardSignal::all_cleared] = true;
    return true;
  }
  return false;
}

int puyoBoard::get_temp_obstruct_puyo_for_sounding() {
  return exchange(temp_obstruct_puyo, 0);
}
void puyoBoard::approve_spawn_obstruct_puyo() {
  approvement_for_obstruct_puyo = true;
}

void puyoBoard::find_energy_puyos(float fx, float fy, float tx, float ty) {
  if (temp_energy_puyos.empty())
    return;
  for (const auto [x, y, color] : temp_energy_puyos)
    energy_puyos.push_back(puyoEnergyPuyo(
        fx + x * PUYO_SIZE, fy + y * PUYO_SIZE, tx, ty, color, BOARD_FLY_TICK));
  temp_energy_puyos.clear();
}
void puyoBoard::clear_temp_energy_puyos() { temp_energy_puyos.clear(); }
