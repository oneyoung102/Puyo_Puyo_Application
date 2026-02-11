#include <vector>
#include <utility>

#include "puyoBoard.hpp"

using namespace std;


puyoBoard::puyoBoard(int x, float y) : board_r(12), board_c(6)
{
    board = vector<vector<int>>(board_r,vector<int>(board_c,-1));
    puyo_appear_x = x;
    puyo_appear_y = y;
}
pair<int,int> puyoBoard::get_board_size(){return make_pair(board_r,board_c);}
bool puyoBoard::is_in_row(int r){return 0 <= r && r < board_r;}
bool puyoBoard::is_in_col(int c){return 0 <= c && c < board_c;}
bool puyoBoard::is_in_board(int r, int c){return is_in_row(r) && is_in_col(c);}//이건 행,열

pair<int,float> puyoBoard::get_puyo_appear_pos(){return make_pair(puyo_appear_x,puyo_appear_y);}

int puyoBoard::get_puyo(int r, int c){return board[r][c];}//이건 행,열
void puyoBoard::insert_puyo(int puyo, int r, int c){board[r][c] = puyo;}//이건 행,열
void puyoBoard::remove_puyo(int r, int c){board[r][c] = -1;}//이건 행,열
