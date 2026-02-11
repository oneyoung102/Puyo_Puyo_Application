#pragma once

#include <vector>
#include <utility>

using namespace std;

class puyoBoard
{
    private :
        vector<vector<int>> board;
        const int board_r, board_c; 
        int puyo_appear_x, puyo_appear_y;

    public :  
        puyoBoard(int x, int y);
        
        pair<int,int> get_board_size();
        bool is_in_row(int r);
        bool is_in_col(int c);
        bool is_in_board(int r, int c);

        pair<int,int> get_puyo_appear_pos();

        int get_puyo(int r, int c);//이건 행,열
        void insert_puyo(int puyo, int r, int c);//이건 행,열
        void remove_puyo(int r, int c);//이건 행,열
};