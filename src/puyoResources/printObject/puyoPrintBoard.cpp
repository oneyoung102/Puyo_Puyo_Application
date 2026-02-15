#include <SFML/Graphics.hpp>
#include "puyoPrintBoard.hpp"
#include "../../puyoPhase/puyoBoard.hpp"
#include "../puyoPrinting.hpp"

puyoPrintBoard::puyoPrintBoard(puyoBoard& b, Sprite puyo, int x, int y, int life) : puyoPrintObject(puyo,x,y,life), board(b){}

void puyoPrintBoard::print_puyo(RenderWindow& w, int img_x, int img_y, int px, int py)
{
    img_x = PUYO_SIZE*img_x, img_y = PUYO_SIZE*img_y;
    sprite.setTextureRect(IntRect({img_x, img_y}, {PUYO_SIZE, PUYO_SIZE})); 
    print_sprite(w,px,py);
}

void puyoPrintBoard::print_object(RenderWindow& w)
{
    const auto [board_r,board_c] = board.get_board_size();
    
    for(int i = 0 ; i < board_r ; ++i)
        for(int j = 0 ; j < board_c ; ++j)
        {
            if(board.get_puyo(i,j) == -1)
                continue;
            const int curr_puyo = board.get_puyo(i,j);
            const int dir = 1*(board.is_in_board(i+1,j) && board.get_puyo(i+1,j) == curr_puyo)+
                            2*(board.is_in_board(i-1,j) && board.get_puyo(i-1,j) == curr_puyo)+
                            4*(board.is_in_board(i,j+1) && board.get_puyo(i,j+1) == curr_puyo)+
                            8*(board.is_in_board(i,j-1) && board.get_puyo(i,j-1) == curr_puyo);
            print_puyo(w,dir,board.get_puyo(i,j),x+PUYO_SIZE*j,y+PUYO_SIZE*i);//0대신 주변 뿌요 감지해서 방향 설정
        }
}