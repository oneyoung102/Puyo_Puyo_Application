#include <SFML/Graphics.hpp>
#include "puyoPrintBoard.hpp"
#include "puyoPage/pages/gamePage/puyoBoard/puyoBoard.hpp"
#include "puyoResources/puyoPrinting/puyoImageConstant.hpp"

using namespace puyoImageConstant;
using namespace std;
using namespace sf;

puyoPrintBoard::puyoPrintBoard(puyoBoard& board, Sprite puyo, int x, int y, int life) : puyoPrintObject(puyo,x,y,life), board(board){}
void puyoPrintBoard::print_object(RenderWindow& w)
{
    const auto [board_r,board_c] = board.get_board_size();
    
    for(int i = 0 ; i < board_r ; ++i)
        for(int j = 0 ; j < board_c ; ++j)
        {
            const puyoType puyo = board.get_puyo(i,j);
            switch(puyo)
            {
                case puyoType::blue :
                case puyoType::red :
                case puyoType::yellow :
                case puyoType::green :
                case puyoType::pupple :
                {
                    const int dir = 1*(board.is_in_board(i+1,j) && board.get_puyo(i+1,j) == puyo)+
                            2*(board.is_in_board(i-1,j) && board.get_puyo(i-1,j) == puyo)+
                            4*(board.is_in_board(i,j+1) && board.get_puyo(i,j+1) == puyo)+
                            8*(board.is_in_board(i,j-1) && board.get_puyo(i,j-1) == puyo);
                    print_16x16(w,dir,(int)puyo,x+PUYO_SIZE*j,y+PUYO_SIZE*i);
                    break;
                }
                default :
                    print_puyo(w,puyo,x+PUYO_SIZE*j,y+PUYO_SIZE*i);
                    break;
            }
        }
}