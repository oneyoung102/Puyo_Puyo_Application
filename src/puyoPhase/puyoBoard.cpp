#include <vector>
#include <utility>

#include "puyoBoard.hpp"
#include "puyoTempPuyo/puyoGravityPuyo.hpp"
#include "puyoTempPuyo/puyoVanishPuyo.hpp"

using namespace std;


puyoBoard::puyoBoard() : board_r(12), board_c(6)
{
    board = vector<vector<int>>(board_r,vector<int>(board_c,-1));
}

pair<float,float> puyoBoard::get_puyo_spawn_pos(){return make_pair(puyo_spawn_x,puyo_spawn_y);}
void puyoBoard::set_puyo_spawn_pos(float x, float y)
{
    puyo_spawn_x = x;
    puyo_spawn_y = y;
};


pair<int,int> puyoBoard::get_board_size(){return make_pair(board_r,board_c);}
bool puyoBoard::is_in_row(int r){return 0 <= r && r < board_r;}
bool puyoBoard::is_in_col(int c){return 0 <= c && c < board_c;}
bool puyoBoard::is_in_board(int r, int c){return is_in_row(r) && is_in_col(c);}//이건 행,열

int puyoBoard::get_puyo(int r, int c){return board[r][c];}//이건 행,열
void puyoBoard::insert_puyo(int puyo, int r, int c){board[r][c] = puyo;}//이건 행,열
void puyoBoard::remove_puyo(int r, int c){board[r][c] = -1;}//이건 행,열


void puyoBoard::push_gravity_puyo(puyoGravityPuyo&& ptp) //std::move
{
    gravity_puyos.push_back(std::move(ptp));
}
void puyoBoard::push_gravity_puyo(vector<puyoGravityPuyo>&& ptp_v)//std::move
{
    for(auto&& ptp : ptp_v)
        push_gravity_puyo(std::move(ptp));
}
void puyoBoard::push_vanish_puyo(puyoVanishPuyo&& ptp) //std::move
{
    vanish_puyos.push_back(std::move(ptp));
}

vector<puyoGravityPuyo>& puyoBoard::get_gravity_puyos(){return gravity_puyos;}
vector<puyoVanishPuyo>& puyoBoard::get_vanish_puyos(){return vanish_puyos;}
bool puyoBoard::not_existed_gravity_puyo(){return gravity_puyos.empty();}
bool puyoBoard::not_existed_vanish_puyo(){return vanish_puyos.empty();}
